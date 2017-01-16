#include "gtest/gtest.h"
#include "ground_gear_intake.h"
#include "queue_types.h"


//FIRST TEST
TEST(GroundGearIntakeTest, CanPickupWithoutCurrentSpike) {
  GroundGearIntake gear_intake = GroundGearIntake();
  GroundGearIntakeInputProto input;
  GroundGearIntakeGoalProto goal;
  GroundGearIntakeOutputProto output;

  goal->set_goal(Goal::PICKUP);
  gear_intake.SetGoal(goal);
  
  for(int i = 0; i < 600; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_TRUE(output->solenoid());
    EXPECT_EQ(output->voltage(), 12.);
  }
}

//SECOND TEST
TEST(GroundGearIntakeTest, CanPickupWithoutCurrentSpike) {
  GroundGearIntake gear_intake = GroundGearIntake();
  GroundGearIntakeInputProto input;
  GroundGearIntakeGoalProto goal;
  GroundGearIntakeOutputProto output;

  goal->set_goal(Goal::CARRY);
  gear_intake.SetGoal(goal);
  
  for(int i = 0; i < 600; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->solenoid());
    EXPECT_EQ(output->voltage(), 12.);
  }
}

//THIRD TEST
TEST(GroundGearIntakeTest, CanPickupWithoutCurrentSpike) {
  GroundGearIntake gear_intake = GroundGearIntake();
  GroundGearIntakeInputProto input;
  GroundGearIntakeGoalProto goal;
  GroundGearIntakeOutputProto output;

  goal->set_goal(Goal::SCORE);
  gear_intake.SetGoal(goal);
  
  for(int i = 0; i < 600; i++) {
    input->set_current(20.);
    output = gear_intake.Update(input);
    EXPECT_FALSE(output->solenoid());
    EXPECT_EQ(output->voltage(), 12.);
  }
}


