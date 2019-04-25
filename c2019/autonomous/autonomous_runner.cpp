#include <sstream>
#include <string>
#include <vector>

#include "c2019/autonomous/autonomous_runner.h"
#include "c2019/commands/rocket.h"

namespace c2019 {
namespace autonomous {

using muan::queues::QueueManager;
using muan::webdash::AutoProto;
using muan::webdash::WebDashQueueWrapper;
using muan::wpilib::DriverStationProto;

AutonomousRunner::AutonomousRunner()
    : driver_station_reader_(
          QueueManager<DriverStationProto>::Fetch()->MakeReader()),
      auto_mode_reader_(WebDashQueueWrapper::GetInstance()
                            .auto_queue()
                            .MakeReader()) {}

void AutonomousRunner::operator()() {
  /* aos::SetCurrentThreadRealtimePriority(10); */
  muan::utils::SetCurrentThreadName("Autonomous");

  muan::wpilib::DriverStationProto driver_station;

  while (!driver_station_reader_.ReadLastMessage(&driver_station)) {
    LOG(WARNING, "No driver station message!");
    loop_.SleepUntilNext();
  }

  while (driver_station_reader_.ReadLastMessage(&driver_station),
         driver_station->mode() != RobotMode::AUTONOMOUS) {
    loop_.SleepUntilNext();
  }

  commands::Rocket rocket_command;

  if ((AutoMode() == "LEFT_BACK_ROCKET")) {
    rocket_command.LeftBackRocket();
  } else if (AutoMode() == "LEFT_SIDE_CARGO_SHIP") {
    rocket_command.LeftSideCargoShip();
  } else if (AutoMode() == "LEFT_FRONT_CARGO_SHIP") {
    rocket_command.LeftFrontCargoShip();
  } else if (AutoMode() == "LEFT_CARGO_ROCKET") {
    rocket_command.LeftCargoRocket();
  } else if (AutoMode() == "LEFT_DOUBLE_ROCKET") {
    rocket_command.LeftDoubleRocket();
  } else if (AutoMode() == "RIGHT_SIDE_CARGO_SHIP") {
    rocket_command.RightSideCargoShip();
  } else if (AutoMode() == "RIGHT_FRONT_CARGO_SHIP") {
    rocket_command.RightFrontCargoShip();
  } else if (AutoMode() == "RIGHT_CARGO_ROCKET") {
    rocket_command.RightCargoRocket();
  } else if (AutoMode() == "RIGHT_DOUBLE_ROCKET") {
    rocket_command.RightDoubleRocket();
  } else if (AutoMode() == "RIGHT_BACK_ROCKET") {
    rocket_command.RightBackRocket();
  }
}

std::string AutonomousRunner::AutoMode() {
  AutoProto auto_mode;
  if (auto_mode_reader_.ReadLastMessage(&auto_mode)) {
    return auto_mode->auto_modes();
  } else {
    return "DRIVE";
  }
}

}  // namespace autonomous
}  // namespace c2019
