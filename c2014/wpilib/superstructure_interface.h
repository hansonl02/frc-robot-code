#ifndef C2014_WPILIB_SUPERSTRUCTURE_INTERFACE_H_
#define C2014_WPILIB_SUPERSTRUCTURE_INTERFACE_H_

#include "WPILib.h"
#include "muan/wpilib/pcm_wrapper.h"
#include "muan/wpilib/can_wrapper.h"
#include "c2014/queue_manager/queue_manager.h"
#include "muan/utils/math_utils.h"

namespace c2014 {
namespace wpilib {

class SuperStructureInterface {
 public:
  explicit SuperStructureInterface(muan::wpilib::CanWrapper* can_wrapper);

  void WriteActuators();
  void ReadSensors();

 private:
  c2014::shooter::ShooterInputQueue shooter_input_queue_;
  c2014::trigger::TriggerInputQueue trigger_input_queue_;
  c2014::climber::ClimberInputQueue climber_input_queue_;

  c2014::magazine::MagazineInputQueue magazine_input_queue_;
  c2014::ground_gear_intake::GroundGearIntakeInputQueue ground_gear_input_queue_;

  c2014::wpilib::WpilibOutputQueue::QueueReader output_queue_;

  VictorSP shooter_motor_;
  VictorSP trigger_motor_;
  VictorSP brush_motor_;
  VictorSP ball_intake_motor_;
  VictorSP gear_intake_motor_;

  Encoder shooter_encoder_;
  Encoder trigger_encoder_;

  muan::wpilib::PcmWrapper* pcm_;
};

}  // namespace wpilib
}  // namespace c2014

#endif  // C2014_WPILIB_SUPERSTRUCTURE_INTERFACE_H_
