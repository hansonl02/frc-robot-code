#include "c2018/teleop/main.h"
#include <string>

namespace c2018 {
namespace teleop {

using DrivetrainGoalProto = frc971::control_loops::drivetrain::GoalProto;
using muan::wpilib::DriverStationProto;
using muan::wpilib::GameSpecificStringProto;
using muan::teleop::JoystickStatusProto;
using muan::queues::QueueManager;
using c2018::climber::ClimberGoalProto;
using c2018::score_subsystem::ScoreSubsystemGoalProto;

TeleopBase::TeleopBase()
    : throttle_{1, QueueManager<JoystickStatusProto>::Fetch("throttle")},
      wheel_{0, QueueManager<JoystickStatusProto>::Fetch("wheel")},
      gamepad_{2, QueueManager<JoystickStatusProto>::Fetch("gamepad")},
      ds_sender_{QueueManager<DriverStationProto>::Fetch(),
                 QueueManager<GameSpecificStringProto>::Fetch()},
      climber_goal_queue_{QueueManager<ClimberGoalProto>::Fetch()},
      score_subsystem_goal_queue_{
          QueueManager<ScoreSubsystemGoalProto>::Fetch()} {
  first_level_height_ =
      gamepad_.MakeButton(uint32_t(muan::teleop::XBox::A_BUTTON));
  second_level_height_ =
      gamepad_.MakeButton(uint32_t(muan::teleop::XBox::B_BUTTON));
  third_level_height_ =
      gamepad_.MakeButton(uint32_t(muan::teleop::XBox::X_BUTTON));
  score_height_ = gamepad_.MakeButton(uint32_t(muan::teleop::XBox::Y_BUTTON));
  initialize_climb_ = gamepad_.MakeButton(uint32_t(muan::teleop::XBox::BACK));
  climb_ = gamepad_.MakeButton(uint32_t(muan::teleop::XBox::START));
  stop_climb_ =
      gamepad_.MakeButton(uint32_t(muan::teleop::XBox::RIGHT_CLICK_IN));
  godmode_ = gamepad_.MakeButton(
      uint32_t(muan::teleop::XBox::LEFT_CLICK_IN));  // TODO(hanson/gemma/ellie)
                                                     // add godmodes for
                                                     // intaking/outtaking

  godmode_elevator_down_ = gamepad_.MakeAxis(1, .7);  // Left Joystick South
  godmode_elevator_up_ = gamepad_.MakeAxis(4, .7);  // TODO(David/Gemma/) Figure
                                                    // out what buttons
                                                    // correspond to what axis

  intake_ = gamepad_.MakeAxis(3, .7);   // Right Trigger
  outtake_ = gamepad_.MakeAxis(2, .7);  // Left Trigger

  score_back_ = gamepad_.MakePov(0, muan::teleop::Pov::kSouth);
  score_front_ = gamepad_.MakePov(0, muan::teleop::Pov::kNorth);

  shifting_low_ = throttle_.MakeButton(4);
  shifting_high_ = throttle_.MakeButton(5);

  quickturn_ = wheel_.MakeButton(5);

  // Default values
  climber_goal_->set_climber_goal(c2018::climber::NONE);

  score_subsystem_goal_->set_elevator_height(c2018::score_subsystem::HEIGHT_0);
  score_subsystem_goal_->set_intake_mode(c2018::score_subsystem::IDLE);
  score_subsystem_goal_->set_claw_mode(c2018::score_subsystem::VERTICAL);
}

void TeleopBase::operator()() {
  aos::time::PhasedLoop phased_loop(std::chrono::milliseconds(20));
  aos::SetCurrentThreadRealtimePriority(10);
  muan::utils::SetCurrentThreadName("TeleopBase");

  LOG_P("Starting TeleopBase thread!");

  running_ = true;
  while (running_) {
    throttle_.Update();
    wheel_.Update();
    gamepad_.Update();
    Update();
    phased_loop.SleepUntilNext();
  }
}

void TeleopBase::Stop() { running_ = false; }

void TeleopBase::Update() {
  if (DriverStation::GetInstance().IsOperatorControl()) {
    SendDrivetrainMessage();
  }

  SetReadableLogName();

  ds_sender_.Send();
}

void TeleopBase::SetReadableLogName() {
  if (DriverStation::GetInstance().GetMatchType() !=
          DriverStation::MatchType::kNone &&
      !log_name_set_) {
    std::string name;
    int match_num = DriverStation::GetInstance().GetMatchNumber();
    std::string match_number = std::to_string(match_num);
    // Figure out name for log file
    switch (DriverStation::GetInstance().GetMatchType()) {
      case DriverStation::MatchType::kNone:
        name = "N" + match_number;
        break;
      case DriverStation::MatchType::kPractice:
        name = "P" + match_number;
        break;
      case DriverStation::MatchType::kQualification:
        name = "Q" + match_number;
        break;
      case DriverStation::MatchType::kElimination:
        name = "E" + match_number;
        break;
    }
    muan::logging::FileWriter::CreateReadableName(name);
    log_name_set_ = true;
  }
}

void TeleopBase::SendDrivetrainMessage() {
  using DrivetrainGoal = frc971::control_loops::drivetrain::GoalProto;
  DrivetrainGoal drivetrain_goal;

  double throttle = -throttle_.wpilib_joystick()->GetRawAxis(1);
  double wheel = -wheel_.wpilib_joystick()->GetRawAxis(0);
  bool quickturn = quickturn_->is_pressed();

  if (shifting_high_->was_clicked()) {
    high_gear_ = true;
  }
  if (shifting_low_->was_clicked()) {
    high_gear_ = false;
  }

  drivetrain_goal->set_gear(
      high_gear_ ? frc971::control_loops::drivetrain::Gear::kHighGear
                 : frc971::control_loops::drivetrain::Gear::kLowGear);

  drivetrain_goal->mutable_teleop_command()->set_steering(wheel);
  drivetrain_goal->mutable_teleop_command()->set_throttle(throttle);
  drivetrain_goal->mutable_teleop_command()->set_quick_turn(quickturn);

  QueueManager<DrivetrainGoal>::Fetch()->WriteMessage(drivetrain_goal);
}

void TeleopBase::SendScoreSubsystemMessage() {
  // Godmode
  if (godmode_->was_clicked()) {
    god_mode_ = !god_mode_;
  }
  if (god_mode_ && godmode_elevator_up_->was_clicked()) {
    // TODO(hanson/gemma/ellie) kyle pls
  }

  // Toggle elevator heights
  if (first_level_height_->was_clicked()) {
    score_subsystem_goal_->set_elevator_height(
        c2018::score_subsystem::HEIGHT_0);
  } else if (second_level_height_->was_clicked()) {
    score_subsystem_goal_->set_elevator_height(
        c2018::score_subsystem::HEIGHT_1);
  } else if (third_level_height_->was_clicked()) {
    score_subsystem_goal_->set_elevator_height(
        c2018::score_subsystem::HEIGHT_2);
  } else if (score_height_->was_clicked()) {
    score_subsystem_goal_->set_elevator_height(
        c2018::score_subsystem::HEIGHT_SCORE);
  }

  // Intake Modes
  if (intake_->is_pressed()) {
    score_subsystem_goal_->set_intake_mode(c2018::score_subsystem::INTAKE);
  } else if (outtake_->is_pressed()) {
    score_subsystem_goal_->set_intake_mode(c2018::score_subsystem::OUTTAKE);
  } else {
    score_subsystem_goal_->set_intake_mode(c2018::score_subsystem::IDLE);
  }

  // Scoring
  if (score_front_->is_pressed()) {
    score_subsystem_goal_->set_claw_mode(c2018::score_subsystem::SCORE_F);
  } else if (score_back_->is_pressed()) {
    score_subsystem_goal_->set_claw_mode(c2018::score_subsystem::SCORE_B);
  } else {
    score_subsystem_goal_->set_claw_mode(c2018::score_subsystem::VERTICAL);
  }
  score_subsystem_goal_queue_->WriteMessage(score_subsystem_goal_);
}

void TeleopBase::SendClimbSubsystemMessage() {
  if (initialize_climb_->was_clicked()) {
    climber_goal_->set_climber_goal(c2018::climber::APPROACHING);
    if (climb_->was_clicked()) {
      climber_goal_->set_climber_goal(c2018::climber::CLIMBING);
    }
  } else if (stop_climb_->was_clicked()) {
    climber_goal_->set_climber_goal(c2018::climber::NONE);
  }
  climber_goal_queue_->WriteMessage(climber_goal_);
}

}  // namespace teleop
}  // namespace c2018
