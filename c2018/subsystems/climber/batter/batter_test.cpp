#include "c2018/subsystems/climber/batter/batter.h"
#include "gtest/gtest.h"

TEST(Batter, CanPutDownBatter) {
<<<<<<< HEAD
  c2018::batter::Batter batter;
=======
  c2018::climber::batter::Batter batter;
>>>>>>> 5fd6abbe78d27a6d651358ae428afe5d3cf40a2f
  EXPECT_TRUE(batter.Update(true, true));
}

TEST(Batter, NotPutDown) {
<<<<<<< HEAD
  c2018::batter::Batter batter;
=======
  c2018::climber::batter::Batter batter;
>>>>>>> 5fd6abbe78d27a6d651358ae428afe5d3cf40a2f
  EXPECT_FALSE(batter.Update(false, true));
}

TEST(Batter, Disabled) {
<<<<<<< HEAD
  c2018::batter::Batter batter;
  EXPECT_FALSE(batter.Update(true, false));
}

TEST(Batter, DisabledAndDontPutDownBatter) {
  c2018::batter::Batter batter;
=======
  c2018::climber::batter::Batter batter;
  EXPECT_FALSE(batter.Update(true, false));
}

TEST(Batter, DisabledAndNotPutDown) {
  c2018::climber::batter::Batter batter;
>>>>>>> 5fd6abbe78d27a6d651358ae428afe5d3cf40a2f
  EXPECT_FALSE(batter.Update(false, false));
}
