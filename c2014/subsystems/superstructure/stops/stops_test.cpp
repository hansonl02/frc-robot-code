#include "c2014/subsystems/superstructure/stops/stops.h"
#include "c2014/subsystems/superstructure/stops/queue_types.h"
#include "gtest/gtest.h"

TEST(StopsTest, CanShootShort) {
  c2014::stops::StopsGoalProto goal;
  c2014::stops::Stops stops;

  goal->set_short_shot(true);

  stops.SetGoal(goal);
  c2014::stops::StopsOutputProto output = stops.Update();

  EXPECT_TRUE(output->short_shot());
}

TEST(StopsTest, CanShootFar) {
  c2014::stops::StopsGoalProto goal;
  c2014::stops::Stops stops;

  goal->set_short_shot(false);

  stops.SetGoal(goal);
  c2014::stops::StopsOutputProto output = stops.Update();

  EXPECT_FALSE(output->short_shot());
}
