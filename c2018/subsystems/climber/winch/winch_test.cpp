#include "c2018/subsystems/climber/winch/winch.h"
#include "gtest/gtest.h"

class WinchTest : public ::testing::Test {
 public:
  WinchTest() {}

  double Update(double encoder, bool outputs_enabled, int num_ticks, bool should_climb) {
    double output;

    for (int i = 0; i < num_ticks; i++) {
      output = winch_.Update(&status_, encoder, should_climb, outputs_enabled);
    }
    return output;
  }
  bool is_reset() { return winch_.is_reset(); }
  bool has_climbed() { return winch_.has_climbed(); }
  c2018::climber::ClimberStatusProto status_;

 private:
  c2018::climber::winch::Winch winch_;
};

TEST_F(WinchTest, Idle) {
  double output = Update(0.0, true, 3000, false);

  EXPECT_NEAR(output, 0.0, 1e-3);
  EXPECT_EQ(status_->climber_state(), c2018::climber::State::IDLE);
  EXPECT_FALSE(has_climbed());
}

TEST_F(WinchTest, Disabled) {
  double output = Update(0.0, false, 3000, true);

  EXPECT_NEAR(output, 0.0, 1e-3);
  EXPECT_EQ(status_->climber_state(), c2018::climber::State::IDLE);
  EXPECT_FALSE(has_climbed());
}

TEST_F(WinchTest, Climb) {
  double output;

  for (int i = 0; i < 5000; i++) {
    output = Update(i, true, 1, true);
  }
  EXPECT_EQ(status_->climber_state(), c2018::climber::State::IDLE);
  EXPECT_NEAR(output, 0.0, 1e-3);
  EXPECT_TRUE(has_climbed());
}

TEST_F(WinchTest, ClimbReset) {
  double output;

  for (int i = 0; i < 200; i++) {
    output = Update(i, true, 1, true);
  }

  EXPECT_EQ(status_->climber_state(), c2018::climber::State::CLIMB);
  EXPECT_FALSE(is_reset());
  EXPECT_NEAR(output, c2018::climber::winch::kRunningVoltage, 1e-3);
  EXPECT_FALSE(has_climbed());

  for (int i = 0; i < 2; i++) {
    output = Update(i, true, 1, false);
  }

  EXPECT_TRUE(is_reset());
  EXPECT_NEAR(output, 0.0, 1e-3);
  EXPECT_EQ(status_->climber_state(), c2018::climber::State::IDLE);
  EXPECT_FALSE(has_climbed());

  for (int i = 0; i < 5000; i++) {
    output = Update(i, true, 1, true);
  }

  EXPECT_FALSE(is_reset());
  EXPECT_NEAR(output, 0.0, 1e-3);
  EXPECT_EQ(status_->climber_state(), c2018::climber::State::IDLE);
  EXPECT_TRUE(has_climbed());
}
