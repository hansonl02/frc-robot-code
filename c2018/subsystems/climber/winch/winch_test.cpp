#include "gtest/gtest.h"
#include "c2018/subsystems/climber/winch/winch.h"

class WinchTest : public ::testing::Test {
  public:
    WinchTest() {}
    
    double Update(double encoder, bool outputs_enabled, int num_ticks, bool should_climb) {
      double output;  
    
      for (int i = 0; i < num_ticks; i++) {
        output = winch_.Update(status_, encoder, should_climb, outputs_enabled);
      }
      return output;
    }
      bool is_reset() { return winch_.is_reset(); } 
  private:
   c2018::climber::winch::Winch winch_;
   c2018::climber::ClimberStatusProto* status_;
};

TEST_F(WinchTest, Idle) {
  double output = Update(0.0, true, 3000,false);
  
  EXPECT_NEAR(output, 0.0, 1e-3);
}

TEST_F(WinchTest, Climb) {
  double output;
  
  for (int i = 0; i < 5000; i++) {
    output = Update(i, true, 1, true);
  }
  EXPECT_NEAR(output, 0.0, 1e-3); 
}

TEST_F(WinchTest, ClimbReset) {
  double output;
  
  for (int i = 0; i < 3000; i++) {
    output = Update(i, true, 1, true);
  }

  EXPECT_FALSE(is_reset());
  EXPECT_NEAR(output, c2018::climber::winch::kRunningVoltage , 1e-3);

  for (int i = 0; i < 2; i++) {
    output = Update(i, false, 1, true);
  }

  EXPECT_TRUE(is_reset());
  EXPECT_NEAR(output, 0.0, 1e-3);

  for (int i = 0; i < 5000;i++) {
    output = Update(i, true, 1, true);
 }
  EXPECT_FALSE(is_reset());
  EXPECT_NEAR(output, c2018::climber::winch::kRunningVoltage, 1e-3);
}  
