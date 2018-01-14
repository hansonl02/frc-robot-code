#include "c2018/subsystems/climber/climber.h"
#include "gtest/gtest.h"
#include "muan/queues/queue_manager.h"

Climber climber;

TEST(ClimberTest, Idle) {
  c2018::climber::ClimberGoalQueue climber_goal_queue;
  c2018::climber::ClimberInputQueue climber_input_queue;
  muan::wpilib::DriverStationQueue driver_station_queue;

  c2018::climber::ClimberGoalProto climber_goal_proto;
  c2018::climber::ClimberInputProto climber_input_proto;
  muan::wpilib::DriverStationProto driver_station_proto;

  climber_goal_proto.set_put_down_batter(false);
  climber_goal_proto.set_climber_goal(NONE);  // TODO(Gemma and Hanson and Tim) continue writing tests

  climber.Update();
}
