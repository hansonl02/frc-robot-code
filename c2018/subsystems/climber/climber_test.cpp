#include "c2018/subsystems/climber/climber.h"
#include "gtest/gtest.h"
#include "muan/queues/queue_manager.h"

c2018::climber::Climber climber;

TEST(ClimberTest, Idle) {
  // CREATING QUEUES
  c2018::climber::ClimberGoalQueue* climber_goal_queue =
      muan::queues::QueueManager<c2018::climber::ClimberGoalProto>::Fetch();
  c2018::climber::ClimberInputQueue* climber_input_queue =
      muan::queues::QueueManager<c2018::climber::ClimberInputProto>::Fetch();
  muan::wpilib::DriverStationQueue* driver_station_queue =
      muan::queues::QueueManager<muan::wpilib::DriverStationProto>::Fetch();
  c2018::climber::ClimberStatusQueue::QueueReader climber_status_queue =
      muan::queues::QueueManager<c2018::climber::ClimberStatusProto>::Fetch()->MakeReader();
  c2018::climber::ClimberOutputQueue::QueueReader climber_output_queue =
      muan::queues::QueueManager<c2018::climber::ClimberOutputProto>::Fetch()->MakeReader();

  // CREATING PROTOS
  c2018::climber::ClimberGoalProto climber_goal_proto;
  c2018::climber::ClimberInputProto climber_input_proto;
  c2018::climber::ClimberStatusProto climber_status_proto;
  c2018::climber::ClimberOutputProto climber_output_proto;
  muan::wpilib::DriverStationProto driver_station_proto;

  // SETTING GOALS & INPUTS
  climber_goal_proto->set_put_down_batter(false);
  climber_goal_proto->set_climber_goal(c2018::climber::Goal::NONE);
  driver_station_proto->set_is_sys_active(true);
  climber_input_proto->set_position(0);

  // WRITING TO QUEUES
  climber_input_queue->WriteMessage(climber_input_proto);
  climber_goal_queue->WriteMessage(climber_goal_proto);
  driver_station_queue->WriteMessage(driver_station_proto);

  climber.Update();

  // READING QUEUES
  climber_output_queue.ReadLastMessage(&climber_output_proto);
  climber_status_queue.ReadLastMessage(&climber_status_proto);

  EXPECT_EQ(climber_output_proto->voltage(), 0.);
  EXPECT_FALSE(climber_output_proto->release_solenoid());
  EXPECT_EQ(climber_status_proto->climber_state(), c2018::climber::State::IDLE);
  EXPECT_EQ(climber_status_proto->observed_velocity(), 0.);
  EXPECT_EQ(climber_status_proto->observed_height(), 0.);
}

TEST(ClimberTest, Approach) {
  // MAKING QUEUES
  c2018::climber::ClimberGoalQueue* climber_goal_queue =
      muan::queues::QueueManager<c2018::climber::ClimberGoalProto>::Fetch();
  c2018::climber::ClimberInputQueue* climber_input_queue =
      muan::queues::QueueManager<c2018::climber::ClimberInputProto>::Fetch();
  muan::wpilib::DriverStationQueue* driver_station_queue =
      muan::queues::QueueManager<muan::wpilib::DriverStationProto>::Fetch();
  c2018::climber::ClimberStatusQueue::QueueReader climber_status_queue =
      muan::queues::QueueManager<c2018::climber::ClimberStatusProto>::Fetch()->MakeReader();
  c2018::climber::ClimberOutputQueue::QueueReader climber_output_queue =
      muan::queues::QueueManager<c2018::climber::ClimberOutputProto>::Fetch()->MakeReader();

  // MAKING PROTOS
  c2018::climber::ClimberGoalProto climber_goal_proto;
  c2018::climber::ClimberInputProto climber_input_proto;
  c2018::climber::ClimberStatusProto climber_status_proto;
  c2018::climber::ClimberOutputProto climber_output_proto;
  muan::wpilib::DriverStationProto driver_station_proto;

  // SETTING GOALS
  climber_goal_proto->set_put_down_batter(true);
  climber_goal_proto->set_climber_goal(c2018::climber::Goal::APPROACHING);
  driver_station_proto->set_is_sys_active(true);

  // SETTING INPUT
  climber_input_proto->set_position(0.0);

  // WRITING GOALS AND INPUT
  climber_input_queue->WriteMessage(climber_input_proto);
  climber_goal_queue->WriteMessage(climber_goal_proto);
  driver_station_queue->WriteMessage(driver_station_proto);

  climber.Update();

  // READING QUEUES
  climber_output_queue.ReadLastMessage(&climber_output_proto);
  climber_status_queue.ReadLastMessage(&climber_status_proto);

  // TEST VALUES
  EXPECT_EQ(climber_output_proto->voltage(), 0.);
  EXPECT_TRUE(climber_output_proto->release_solenoid());
  EXPECT_EQ(climber_status_proto->climber_state(), c2018::climber::State::APPROACH);
  EXPECT_EQ(climber_status_proto->observed_velocity(), 0.);
  EXPECT_EQ(climber_status_proto->observed_height(), 0.);
}

TEST(ClimberTest, Climb) {
  // CREATING QUEUES
  c2018::climber::ClimberGoalQueue* climber_goal_queue =
      muan::queues::QueueManager<c2018::climber::ClimberGoalProto>::Fetch();
  c2018::climber::ClimberInputQueue* climber_input_queue =
      muan::queues::QueueManager<c2018::climber::ClimberInputProto>::Fetch();
  muan::wpilib::DriverStationQueue* driver_station_queue =
      muan::queues::QueueManager<muan::wpilib::DriverStationProto>::Fetch();
  c2018::climber::ClimberStatusQueue::QueueReader climber_status_queue =
      muan::queues::QueueManager<c2018::climber::ClimberStatusProto>::Fetch()->MakeReader();
  c2018::climber::ClimberOutputQueue::QueueReader climber_output_queue =
      muan::queues::QueueManager<c2018::climber::ClimberOutputProto>::Fetch()->MakeReader();

  // CREATING PROTOS
  c2018::climber::ClimberGoalProto climber_goal_proto;
  c2018::climber::ClimberInputProto climber_input_proto;
  c2018::climber::ClimberStatusProto climber_status_proto;
  c2018::climber::ClimberOutputProto climber_output_proto;
  muan::wpilib::DriverStationProto driver_station_proto;

  // SETTING GOALS
  climber_goal_proto->set_put_down_batter(true);
  climber_goal_proto->set_climber_goal(c2018::climber::Goal::CLIMBING);
  driver_station_proto->set_is_sys_active(true);

  // WRITING GOAL AND DS STATUS
  climber_goal_queue->WriteMessage(climber_goal_proto);
  driver_station_queue->WriteMessage(driver_station_proto);

  // UPDATING CLIMBER
  for (int i = 0; i < 200; i++) {
    climber_input_proto->set_position(i);
    climber_input_queue->WriteMessage(climber_input_proto);
    climber.Update();
  }

  // CHECKING HALFWAY THROUGH CLIMB
  climber_status_queue.ReadLastMessage(&climber_status_proto);
  EXPECT_EQ(climber_status_proto->climber_state(), c2018::climber::State::CLIMB);

  // UPDATING FOR LONGER
  for (int i = 0; i < 3000; i++) {
    climber_input_proto->set_position(i);
    climber_input_queue->WriteMessage(climber_input_proto);
    climber.Update();
  }

  // READING QUEUES
  climber_output_queue.ReadLastMessage(&climber_output_proto);
  climber_status_queue.ReadLastMessage(&climber_status_proto);

  // TESTING OUTPUTS
  EXPECT_EQ(climber_output_proto->voltage(), 0.);
  EXPECT_TRUE(climber_output_proto->release_solenoid());
  EXPECT_EQ(climber_status_proto->climber_state(), c2018::climber::State::DONE);
  EXPECT_EQ(climber_status_proto->observed_velocity(), 0.);
  EXPECT_EQ(climber_status_proto->observed_height(), 0.);
}
