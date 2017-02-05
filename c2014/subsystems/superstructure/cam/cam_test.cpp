#include "c2014/subsystems/superstructure/cam/cam.h"
#include "c2014/subsystems/superstructure/cam/queue_types.h"
#include "gtest/gtest.h"

TEST(CamTest, CanBeIdle) {
  c2014::cam::CamInputProto input;
  c2014::cam::CamGoalProto goal;
  c2014::cam::Cam cam;

  goal->set_cam_goal(c2014::cam::CamGoalState::CAM_IDLE);
  input->set_ready_to_shoot(false);
  cam.SetGoal(goal);
  c2014::cam::CamOutputProto output = cam.Update(input);

  EXPECT_EQ(output->cam_voltage(), 0);
}

TEST(CamTest, CamPrepare) {
  c2014::cam::CamInputProto input;
  c2014::cam::CamGoalProto goal;
  c2014::cam::Cam cam;

  goal->set_cam_goal(c2014::cam::CamGoalState::CAM_PREPARE);
  input->set_ready_to_shoot(false);
  cam.SetGoal(goal);
  c2014::cam::CamOutputProto output = cam.Update(input);

  EXPECT_EQ(output->cam_voltage(), 3);
}

TEST(CamTest, CamShoot) {
  c2014::cam::CamInputProto input;
  c2014::cam::CamGoalProto goal;
  c2014::cam::Cam cam;

  goal->set_cam_goal(c2014::cam::CamGoalState::CAM_SHOOT);
  input->set_ready_to_shoot(true);
  cam.SetGoal(goal);
  c2014::cam::CamOutputProto output = cam.Update(input);

  EXPECT_EQ(output->cam_voltage(), 5);
}

TEST(CamTest, CamShootBeforePrepared) {
  c2014::cam::CamInputProto input;
  c2014::cam::CamGoalProto goal;
  c2014::cam::Cam cam;

  goal->set_cam_goal(c2014::cam::CamGoalState::CAM_SHOOT);
  input->set_ready_to_shoot(false);
  cam.SetGoal(goal);
  c2014::cam::CamOutputProto output = cam.Update(input);

  EXPECT_EQ(output->cam_voltage(), 5);
}

TEST(CamTest, CamPrepareAfterBeingReady) {
  c2014::cam::CamInputProto input;
  c2014::cam::CamGoalProto goal;
  c2014::cam::Cam cam;

  goal->set_cam_goal(c2014::cam::CamGoalState::CAM_PREPARE);
  input->set_ready_to_shoot(true);
  cam.SetGoal(goal);
  c2014::cam::CamOutputProto output = cam.Update(input);

  EXPECT_EQ(output->cam_voltage(), 0);
}
