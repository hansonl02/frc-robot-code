#ifndef C2017_WPILIBUPDATE_MAIN_H_
#define C2017_WPILIBUPDATE_MAIN_H_

#include "muan/teleop/joystick.h"

namespace c2017 {

namespace citrus_robot {

class CitrusRobot {
 public:
  CitrusRobot();

  // Call this to update at ~50hz (DS update rate)
  void Update();

 private:
  muan::teleop::Joystick throttle_, wheel_;
  muan::teleop::Joystick gamepad_;

  bool high_gear_;
  muan::teleop::Button *shifting_high_, *shifting_low_;
  muan::teleop::Button* quickturn_;

  void SendDSMessage();
};

}  // citrus_robot

}  // c2017

#endif  // C2017_WPILIBUPDATE_MAIN_H_
