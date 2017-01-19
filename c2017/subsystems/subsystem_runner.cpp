#include "subsystem_runner.h"

namespace c2017 {

SubsystemRunner::SubsystemRunner()
    : drivetrain_{::c2017::drivetrain::GetDrivetrainConfig(),
                  QueueManager::GetInstance().drivetrain_goal_queue(),
                  QueueManager::GetInstance().drivetrain_input_queue(),
                  QueueManager::GetInstance().drivetrain_output_queue(),
                  QueueManager::GetInstance().drivetrain_status_queue(),
                  QueueManager::GetInstance().driver_station_queue(),
                  QueueManager::GetInstance().gyro_queue()},
      superstructure_{QueueManager::GetInstance().intake_group_goal_queue(),
                  QueueManager::GetInstance().shooter_group_goal_queue(),
                  QueueManager::GetInstance().climber_goal_queue(),
                  QueueManager::GetInstance().shooter_input_queue(),
                  QueueManager::GetInstance().trigger_input_queue(),
                  QueueManager::GetInstance().magazine_input_queue(),
                  QueueManager::GetInstance().ground_gear_input_queue(),
                  QueueManager::GetInstance().ball_intake_input_queue(),
                  QueueManager::GetInstance().climber_input_queue(),
                  QueueManager::GetInstance().driver_station_queue(),
                  } {}

void SubsystemRunner::operator()() {
  aos::time::PhasedLoop phased_loop(std::chrono::milliseconds(5));

  // TODO(Kyle or Wesley) Come up with some actual value for this...
  aos::SetCurrentThreadRealtimePriority(10);
  aos::SetCurrentThreadName("SubsystemRunner");

  running_ = true;

  while (running_) {
    wpilib_.ReadSensors();

    drivetrain_.Update();

    superstructure_.Update();

    wpilib_.WriteActuators();

    phased_loop.SleepUntilNext();
  }
}

void SubsystemRunner::Stop() { running_ = false; }
}
