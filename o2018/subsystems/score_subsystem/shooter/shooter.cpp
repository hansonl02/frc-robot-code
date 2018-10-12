#include "o2018/subsystems/score_subsystem/shooter/shooter.h"

namespace o2018 {
namespace subsystems {
namespace score_subsystem {
namespace shooter {

void Shooter::SetGoal(double angle, IntakeMode intake_goal) {
  unprofiled_goal_ = {muan::utils::Cap(angle, kMinAngle, kMaxAngle), 0.};
  intake_goal_ = intake_goal;
}

void Shooter::Update(const ScoreSubsystemInputProto& input,
                  ScoreSubsystemOutputProto* output,
                  ScoreSubsystemStatusProto* status, bool outputs_enabled) {
  bool has_cube = pinch_state_ == IDLE_WITH_CUBE && input->intake_proxy();

  // Start of intake
  bool intake_solenoid_close = false;
  bool intake_solenoid_open = false;
  double intake_voltage = 0.0;

  if (outputs_enabled) {
    switch (intake_goal_) {
      case IntakeMode::INTAKE:
        intake_voltage = kIntakeVoltage;
        intake_solenoid_close = false;
        intake_solenoid_open = false;
        break;
      case IntakeMode::INTAKE_OPEN:
        intake_voltage = kIntakeVoltage;
        intake_solenoid_close = false;
        intake_solenoid_open = true;
        break;
      case IntakeMode::INTAKE_CLOSE:
      case IntakeMode::SETTLE:
        intake_voltage = kIntakeVoltage;
        intake_solenoid_close = true;
        intake_solenoid_open = false;
        break;
      case IntakeMode::OUTTAKE_SLOW:
        intake_voltage = kSlowOuttakeVoltage;
        intake_solenoid_close = true;
        intake_solenoid_open = false;
        break;
      case IntakeMode::OUTTAKE_FAST:
        intake_voltage = kFastOuttakeVoltage;
        intake_solenoid_close = true;
        intake_solenoid_open = false;
        break;
      case IntakeMode::DROP:
        intake_voltage = 0;
        intake_solenoid_close = false;
        intake_solenoid_open = true;
        break;
      case IntakeMode::INTAKE_NONE:
        if (has_cube) {
          intake_voltage = kHoldingVoltage;
        } else {
          intake_voltage = 0;
        }
        intake_solenoid_close = true;
        intake_solenoid_open = false;
        break;
    }
  } else {
    intake_voltage = 0;
  }

  (*output)->set_intake_voltage(intake_voltage);
  (*output)->set_intake_open(intake_solenoid_open);
  (*output)->set_intake_close(intake_solenoid_close);

  // Logic to make sure it actually has a cube
  switch (pinch_state_) {
    case MOVING:
      if (intake_solenoid_close) {
        has_cube_for_ticks_--;
      } else {
        has_cube_for_ticks_ = kNumHasCubeTicks;
      }
      if (has_cube_for_ticks_ < 0) {
        pinch_state_ = IDLE_WITH_CUBE;
      }
      break;
    case IDLE_WITH_CUBE:
      if (intake_solenoid_open) {
        pinch_state_ = IDLE_NO_CUBE;
      }
      break;
    case IDLE_NO_CUBE:
      if (intake_solenoid_close) {
        pinch_state_ = MOVING;
      }
      break;
  }
  (*status)->set_has_cube(has_cube);
  (*status)->set_intake_state(intake_goal_);
}

void Shooter::UpdateProfiledGoal(bool outputs_enabled) {
  muan::control::TrapezoidalMotionProfile profile =
      muan::control::TrapezoidalMotionProfile(kConstraints, unprofiled_goal_,
                                              profiled_goal_);
  if (outputs_enabled) {
    profiled_goal_ = profile.Calculate(10 * muan::units::ms);
  } else {
    profiled_goal_ = profile.Calculate(0);
  }
}

double Shooter::CalculateFeedForwards(bool has_cube, double elevator_accel) {
  // Magic function goes here
  (void)has_cube;
  (void)elevator_accel;
  return 0.;
}

double Shooter::TimeLeftUntil(double target_angle, double final_angle) {
  if (profiled_goal_.position > target_angle) {
    return 0.;  // We don't care about the backwards profile; we're safe
  }

  muan::control::TrapezoidalMotionProfile profile =
      muan::control::TrapezoidalMotionProfile(kConstraints, {final_angle, 0},
                                              profiled_goal_);
  return profile.TimeLeftUntil(target_angle);
}

}  // namespace shooter
}  // namespace score_subsystem
}  // namespace subsystems
}  // namespace o2018
