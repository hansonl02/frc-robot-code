#ifndef C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_
#define C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_

#include <cmath>
#include "c2018/subsystems/climber/climber.pb.h"
#include "c2018/subsystems/climber/queue_types.h"

namespace c2018 {

namespace climber {

namespace winch {

double kWinchRadius = 3; // WRONG
double kAmountToClimb = 14; // Inches
double kRunningVoltage = 6.0;

class Winch {
 public:
  Winch();

  double Update(c2018::climber::ClimberStatusProto *status, double encoder_i, bool should_climb, bool outputs_enabled);

  bool is_reset() { return reset_; }

 private:
  double rope_climbed_;
  bool reset_ = true;
  double first_enc_pos_;
};

} // namespace winch

} // namespace climber

} // namespace c2018

#endif // C2018_SUBSYSTEMS_CLIMBER_WINCH_WINCH_H_
