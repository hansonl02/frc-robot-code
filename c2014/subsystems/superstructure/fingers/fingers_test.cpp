#include "c2014/subsystems/superstructure/fingers/fingers.h"
#include "c2014/subsystems/superstructure/fingers/queue_types.h"
#include "gtest/gtest.h"

TEST(FingersTest, CanShootShort) {
  c2014::fingers::FingersGoalProto goal;
  c2014::fingers::Fingers fingers;

  goal->set_fingers_goal(c2014::fingers::FingersGoalState::SHORT);

  fingers.SetGoal(goal);
  c2014::fingers::FingersOutputProto output = fingers.Update();

  EXPECT_FALSE(output->close_upper_fingers());
  EXPECT_TRUE(output->close_lower_fingers());
}

TEST(FingersTest, CanIntake) {
  c2014::fingers::FingersGoalProto goal;
  c2014::fingers::Fingers fingers;

  goal->set_fingers_goal(c2014::fingers::FingersGoalState::INTAKING);

  fingers.SetGoal(goal);
  c2014::fingers::FingersOutputProto output = fingers.Update();

  EXPECT_FALSE(output->close_upper_fingers());
  EXPECT_FALSE(output->close_lower_fingers());
}

TEST(FingersTest, CanShootLong) {
  c2014::fingers::FingersGoalProto goal;
  c2014::fingers::Fingers fingers;

  goal->set_fingers_goal(c2014::fingers::FingersGoalState::LONG);

  fingers.SetGoal(goal);
  c2014::fingers::FingersOutputProto output = fingers.Update();

  EXPECT_TRUE(output->close_upper_fingers());
  EXPECT_FALSE(output->close_lower_fingers());
}
