#include "c2019/commands/drive_straight.h"
#include "c2019/subsystems/limelight/queue_types.h"
#include "muan/queues/queue_manager.h"

namespace c2019 {
namespace commands {

using muan::queues::QueueManager;
using muan::wpilib::DriverStationProto;
using c2019::limelight::LimelightStatusProto;

bool DriveStraight::IsAutonomous() {
  DriverStationProto driver_station;
  AutoGoalProto auto_goal;
  if (!driver_station_reader_.ReadLastMessage(&driver_station)) {
    LOG(WARNING, "No driver station status found.");
    return false;
  }

  if (!driver_station->is_sys_active()) {
    LOG(WARNING, "Tried to run command while disabled.");
    return false;
  }

  if (!auto_goal_reader_.ReadLastMessage(&auto_goal)) {
    LOG(WARNING, "No auto goal found.");
    return false;
  }

  if (auto_goal->run_command() && auto_goal->command() == DRIVE_STRAIGHT) {
    return true;
  }

  return false;
}

void DriveStraight::operator()() {
  std::cout << "starting drive straight" << std::endl;
  EnterAutonomous();
  std::cout << "starting drive straight" << std::endl;
  LimelightStatusProto status;
  std::cout << "starting drive straight" << std::endl;
  if (!QueueManager<LimelightStatusProto>::Fetch()->ReadLastMessage(&status)) {
    std::cout << "starting drive straight" << std::endl;
    LOG(WARNING, "No limelight status message provided.");
    ExitAutonomous();
    return;
  }

  if (!status->has_target()) {
  std::cout << "starting drive straight" << std::endl;
    LOG(WARNING, "we fucked up sorry livy");
    ExitAutonomous();
    return;
  }
  std::cout << "starting drive straight" << std::endl;
  
  StartDriveVision();
  LOG(INFO, "Running VISION auto");
  std::cout << "starting drive straight" << std::endl;

  StartDrivePath(1.0, 0, 0, 1, false);
  WaitUntilDriveComplete();  // :)
  ExitAutonomous();
  std::cout << "ending drive straight" << std::endl;
}

}  // namespace commands
}  // namespace c2019
