#include "c2018/subsystems/score_subsystem/score_subsystem.h"

#include <algorithm>

namespace c2018 {
namespace score_subsystem {

using muan::queues::QueueManager;
using muan::wpilib::DriverStationProto;

ScoreSubsystem::ScoreSubsystem() {}

void ScoreSubsystem::BoundGoal(double* elevator_goal, double* wrist_goal) {
  // Elevator goal doesn't get too low if the wrist can't handle it
  if (wrist_status_.wrist_angle > kWristSafeAngle) {
    *elevator_goal = muan::utils::Cap(*elevator_goal, kElevatorWristSafeHeight,
                                      elevator::kElevatorMaxHeight);
  }

  double time_until_elevator_safe =
      elevator_.TimeLeftUntil(kElevatorWristSafeHeight, *elevator_goal);
  double time_until_wrist_safe =
      wrist_.TimeLeftUntil(kWristSafeAngle, wrist::kWristMaxAngle);

  wrist_status_.set_elevator_time_left(time_until_elevator_safe);
  wrist_status_.set_wrist_time_left(time_until_wrist_safe);

  // Wrist doesn't try to go too far if the elevator can't handle it
  if (*wrist_goal > kWristSafeAngle &&
      time_until_elevator_safe > time_until_wrist_safe) {
    *wrist_goal = 0.0;
  }
}

void ScoreSubsystem::Update() {
  // All the logic in the state machine is in this function
  RunStateMachine();

  // These are the goals before they get safety-ized
  double constrained_elevator_height = elevator_height_;
  double constrained_wrist_angle = wrist_angle_;

  // Now we make them safe so stuff doesn't break
  BoundGoal(&constrained_elevator_height, &constrained_wrist_angle);

  // Then we tell the controller to do it
  elevator_.SetGoal(constrained_elevator_height);
  elevator_.Update(outputs_enabled);

  wrist_.SetGoal(constrained_wrist_angle, intake_goal_);
  wrist_.Update(outputs_enabled);

  status_.set_state(state_);
  status_.set_intake_state(intake_goal_);
}

void ScoreSubsystem::SetGoal(ScoreSubsystemGoal goal) {
  // These set the member variable goals before they are constrained
  // They are set based on the score goal enumerator
  switch (goal.score_goal) {
    case SCORE_NONE:
      break;
    case INTAKE_0:
      elevator_height_ = kElevatorIntake0;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case INTAKE_1:
      elevator_height_ = kElevatorIntake1;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case INTAKE_2:
      elevator_height_ = kElevatorIntake2;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case STOW:
      elevator_height_ = kElevatorStow;
      wrist_angle_ = kWristStowAngle;
      whisker_ = false;
      break;
    case SWITCH:
      elevator_height_ = kElevatorSwitch;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case SCALE_LOW_FORWARD:
      elevator_height_ = kElevatorBaseHeight;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case SCALE_LOW_REVERSE:
      elevator_height_ = kElevatorBaseHeight + kElevatorReversedOffset;
      wrist_angle_ = kWristBackwardAngle;
      whisker_ = true;
      break;
    case SCALE_MID_FORWARD:
      elevator_height_ = kElevatorBaseHeight + kCubeHeight;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case SCALE_MID_REVERSE:
      elevator_height_ =
          kElevatorBaseHeight + kCubeHeight + kElevatorReversedOffset;
      wrist_angle_ = kWristBackwardAngle;
      whisker_ = false;
      break;
    case SCALE_HIGH_FORWARD:
      elevator_height_ = kElevatorBaseHeight + 2 * kCubeHeight;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case SCALE_HIGH_REVERSE:
      elevator_height_ =
          kElevatorBaseHeight + 2 * kCubeHeight + kElevatorReversedOffset;
      wrist_angle_ = kWristBackwardAngle;
      whisker_ = false;
      break;
    case SCALE_SUPER_HIGH_FORWARD:
      elevator_height_ = elevator::kElevatorMaxHeight - 0.02;
      wrist_angle_ = kWristTiltUpAngle;
      whisker_ = false;
      break;
    case SCALE_SUPER_HIGH_REVERSE:
      elevator_height_ =
          kElevatorBaseHeight + 3 * kCubeHeight + kElevatorReversedOffset;
      wrist_angle_ = kWristBackwardAngle;
      whisker_ = false;
      break;
    case SCALE_SHOOT:
      elevator_height_ =
          kElevatorBaseHeight + kCubeHeight + kElevatorReversedOffset;
      wrist_angle_ = kWristShootAngle;
      whisker_ = false;
      break;
    case EXCHANGE:
      elevator_height_ = kElevatorExchange;
      wrist_angle_ = kWristForwardAngle;
      whisker_ = false;
      break;
    case PORTAL:
      elevator_height_ = kElevatorPortal;
      wrist_angle_ = kWristPortalAngle;
      whisker_ = false;
      break;
  }

  elevator_height_ += goal.elevator_god_mode_goal * 0.005;
  wrist_angle_ += goal.wrist_god_mode_goal * 0.005;

  elevator_height_ = muan::utils::Cap(
      elevator_height_, c2018::score_subsystem::elevator::kElevatorMinHeight,
      c2018::score_subsystem::elevator::kElevatorMaxHeight);
  wrist_angle_ = muan::utils::Cap(
      wrist_angle_, c2018::score_subsystem::wrist::kWristMinAngle,
      c2018::score_subsystem::wrist::kWristMaxAngle);

  switch (goal.intake_goal) {
    case IntakeGoal::INTAKE_NONE:
      GoToState(ScoreSubsystemState::HOLDING);
      break;
    case IntakeGoal::INTAKE:
    case IntakeGoal::INTAKE_OPEN:
    case IntakeGoal::INTAKE_CLOSE:
      if (!wrist_status_.has_cube) {
        // If we're at the ground level, go to stow afterwards
        if (elevator_height_ < 1e-5 && wrist_angle_ < 1e-5) {
          GoToState(ScoreSubsystemState::INTAKING_TO_STOW, goal.intake_goal);
        } else {
          GoToState(ScoreSubsystemState::INTAKING_ONLY, goal.intake_goal);
        }
      }
      break;
    case IntakeGoal::SETTLE:
    case IntakeGoal::OUTTAKE_SLOW:
    case IntakeGoal::OUTTAKE_FAST:
    case IntakeGoal::DROP:
      GoToState(ScoreSubsystemState::HOLDING, goal.intake_goal);
      break;
  }
}

void ScoreSubsystem::RunStateMachine() {
  // This is the logic to move between 'states'
  switch (state_) {
    case ScoreSubsystemState::CALIBRATING:
      // Stow after calibrating
      elevator_height_ = status_.elevator_height;
      wrist_angle_ = status_.wrist_angle;
      if (wrist_status_.calibrated && elevator_status_.calibrated) {
        // These need to be set right away because calibration moves the
        // goalposts.
        elevator_height_ = kElevatorStow;
        wrist_angle_ = kWristStowAngle;

        GoToState(HOLDING);
      }
      break;
    case HOLDING:
      break;
    case INTAKING_ONLY:
      if (wrist_status_.has_cube) {
        GoToState(HOLDING);
      }
      break;
    case INTAKING_TO_STOW:
      if (wrist_status_.has_cube) {
        elevator_height_ = kElevatorStow;
        wrist_angle_ = kWristStowAngle;
        GoToState(HOLDING);
      }
      break;
  }
}

void ScoreSubsystem::GoToState(ScoreSubsystemState desired_state,
                               IntakeGoal intake) {
  switch (state_) {
    case ScoreSubsystemState::CALIBRATING:
      if (wrist_status_.is_calibrated && elevator_.is_calibrated) {
        state_ = desired_state;
      }
      break;
    case ScoreSubsystemState::INTAKING_ONLY:
    case ScoreSubsystemState::INTAKING_TO_STOW:
    case ScoreSubsystemState::HOLDING:
      if (desired_state == ScoreSubsystemState::INTAKING_ONLY ||
          desired_state == ScoreSubsystemState::INTAKING_TO_STOW) {
        if (intake == IntakeGoal::INTAKE || intake == IntakeGoal::INTAKE_OPEN ||
            intake == IntakeGoal::INTAKE_CLOSE) {
          intake_goal_ = intake;
        }
      } else {
        if (intake == IntakeGoal::INTAKE_NONE || intake == IntakeGoal::SETTLE ||
            intake == IntakeGoal::OUTTAKE_SLOW ||
            intake == IntakeGoal::OUTTAKE_FAST || intake == IntakeGoal::DROP) {
          intake_goal_ = intake;
        }
      }
      state_ = desired_state;
      break;
  }
}

}  // namespace score_subsystem
}  // namespace c2018
