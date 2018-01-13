#include "c2018/subsystems/climber/winch/winch.h"

namespace c2018 {

namespace climber {

namespace winch {

Winch::Winch() {}

double Winch::Update(c2018::climber::ClimberStatusProto *status, double encoder_i, bool should_climb,
                     bool outputs_enabled) {
  double encoder = encoder_i - first_enc_pos_;
  double voltage = 0.;

  rope_climbed_ = kWinchRadius * M_PI / 256 * encoder;

  if (reset_) {
    first_enc_pos_ = encoder_i;
  }

  if (should_climb) {
    (*status)->set_climber_state(c2018::climber::State::CLIMB);
    voltage = kRunningVoltage;
    reset_ = false;
  } else {
    voltage = 0.0;
    reset_ = true;
  }

  if (rope_climbed_ >= kAmountToClimb) {
    voltage = 0.;
  }
  return voltage;
}

}  // namespace winch

}  // namespace climber

}  // namespace c2018
