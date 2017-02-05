#include "c2014/subsystems/superstructure/secondaries/secondaries.h"
#include "c2014/subsystems/superstructure/secondaries/queue_types.h"
#include "gtest/gtest.h"

TEST(SecondariesTest, CanBeIdle) {
  c2014::secondaries::SecondariesGoalProto goal;
  c2014::secondaries::Secondaries secondaries;

  goal->set_secondaries_goal(c2014::secondaries::SecondariesGoalState::IDLE);

  secondaries.SetGoal(goal);
  c2014::secondaries::SecondariesOutputProto output = secondaries.Update();

  EXPECT_TRUE(output->secondaries_open());
  EXPECT_EQ(output->secondaries_voltage(), 0);
}

TEST(SecondariesTest, CanShoot) {
  c2014::secondaries::SecondariesGoalProto goal;
  c2014::secondaries::Secondaries secondaries;

  goal->set_secondaries_goal(c2014::secondaries::SecondariesGoalState::SHOOT);

  secondaries.SetGoal(goal);
  c2014::secondaries::SecondariesOutputProto output = secondaries.Update();

  EXPECT_TRUE(output->secondaries_open());
  EXPECT_EQ(output->secondaries_voltage(), 0);
}

TEST(SecondariesTest, CanSettle) {
  c2014::secondaries::SecondariesGoalProto goal;
  c2014::secondaries::Secondaries secondaries;

  goal->set_secondaries_goal(c2014::secondaries::SecondariesGoalState::SETTLE);

  secondaries.SetGoal(goal);
  c2014::secondaries::SecondariesOutputProto output = secondaries.Update();

  EXPECT_FALSE(output->secondaries_open());
  EXPECT_EQ(output->secondaries_voltage(), 12);
}

TEST(SecondariesTest, CanBarfBack) {
  c2014::secondaries::SecondariesGoalProto goal;
  c2014::secondaries::Secondaries secondaries;

  goal->set_secondaries_goal(c2014::secondaries::SecondariesGoalState::BARF_BACK);

  secondaries.SetGoal(goal);
  c2014::secondaries::SecondariesOutputProto output = secondaries.Update();

  EXPECT_FALSE(output->secondaries_open());
  EXPECT_EQ(output->secondaries_voltage(), -12);
}
