#ifndef C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_
#define C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_

#include <cmath>

namespace c2018 {

namespace climber {

namespace winch {

double kWinchRadius = 3; // WRONG
double kAmountToClimb = 14; // Inches
double kRunningVoltage = 6.0;

class Winch {
 public:
  Winch();

  double Update(double encoder, bool should_climb, bool outputs_enabled);

 private:
  double rope_climbed_;
};

} // namespace winch

} // namespace climber

} // namespace c2018

#endif // C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_
