#ifndef C2017_WPILIB_SUPERSTRUCTURE_INTERFACE_H_
#define C2017_WPILIB_SUPERSTRUCTURE_INTERFACE_H_

#include "WPILib.h"
#include "c2017/queue_manager/queue_manager.h"
#include "muan/utils/math_utils.h"

namespace c2017 {

namespace wpilib {

class SuperStructureInterface {
 public:
  SuperStructureInterface();

  void WriteActuators();
  void ReadSensors();

 private:
  c2017::wpilib_proto::WpilibOutputQueue* output_queue_;
  c2017::wpilib_proto::WpilibInputQueue* input_queue_;

  VictorSP shooter_motor_a_, shooter_motor_b_, shooter_motor_c_, shooter_motor_d_;
  VictorSP trigger_motor_;
  VictorSP brush_motor_;
  VictorSP ball_intake_motor_a_, ball_intake_motor_b_;
  VictorSP gear_intake_motor_;

  Encoder shooter_encoder_;
  Encoder trigger_encoder_;
   

};

}

}

#endif // C2017_WPILIB_SUPERSTURCTURE_INTERFACE_H_
