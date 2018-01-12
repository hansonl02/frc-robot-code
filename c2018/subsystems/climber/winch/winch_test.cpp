#include "gtest/gtest.h"
#include "c2018/subsystems/climber/winch.h"

class WinchTest : public ::testing::Test {
  public:
    WinchTest() {}
    
    void Update(double encoder, bool outputs_enabled, int num_ticks) {
      for (int i = 0; i < num_ticks; i++) {

      }
    }

      
  private:
   c2018::winch::Winch winch;
   
};
