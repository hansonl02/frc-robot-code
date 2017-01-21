#include "ground_gear_intake.h"
#include "queue_types.h"
#include "gtest/gtest.h"

TEST(GroundGearIntakeTest, CanPickupWithoutCurrentSpike) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 12., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanCarryWithoutCurrentSpike) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::CARRY);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanScoreWithoutCurrentSpike) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::SCORE);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), -12., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanScoreWithCurrentSpike) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::SCORE);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(134.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), -12., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanCarryAfterPickingUpStalls) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 600; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 12., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 300; i++) {
    input->set_current(134.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::CARRY);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanScoreAfterCarrying) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::CARRY);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::SCORE);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), -12., 1e-5);
  }
}

TEST(GroundGearIntakeTest, CanScoreAfterPickup) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 12., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::SCORE);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 1000; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), -12., 1e-5);
  }
}

TEST(GroundGearIntakeTest, PickupStallCarryPickup) {
  c2017::ground_gear_intake::GroundGearIntake gear_intake;
  c2017::ground_gear_intake::GroundGearIntakeInputProto input;
  c2017::ground_gear_intake::GroundGearIntakeGoalProto goal;
  c2017::ground_gear_intake::GroundGearIntakeOutputProto output;

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 12., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(134.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::CARRY);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(0.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 0., 1e-5);
  }

  goal->set_goal(c2017::ground_gear_intake::GroundGearIntakeGoal::PICKUP);
  gear_intake.SetGoal(goal);

  for (int i = 0; i < 100; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->intake_down());
    EXPECT_NEAR(output->roller_voltage(), 12., 1e-5);
  }
}