#include "c2018/subsystems/climber/winch/winch.h"

namespace c2018 {

namespace climber{

namespace winch {

Winch::Winch() {}

double Winch::Update(double encoder, bool should_climb, bool outputs_enabled) {
  double voltage = 0.;
  rope_climbed_ = kWinchRadius*M_PI/256*encoder; 

  if (should_climb) {
    voltage = kRunningVoltage;
  } else {
    voltage =  0.0;
  }

  if (rope_climbed_ >= kAmountToClimb) {
    voltage =  0.;
  }
  return voltage;
}

} //namespace winch

} //namespace climber

} // namespace c2018
