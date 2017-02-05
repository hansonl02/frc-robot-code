#ifndef C2014_WPILIB_WPILIB_INTERFACE_H_
#define C2014_WPILIB_WPILIB_INTERFACE_H_

#include "WPILib.h"
#include "muan/wpilib/can_wrapper.h"
#include "muan/wpilib/gyro/gyro_reader.h"
#include "c2014/queue_manager/queue_manager.h"
#include "muan/utils/math_utils.h"

#include "c2014/wpilib/drivetrain_interface.h"
#include "c2014/wpilib/superstructure_interface.h"

namespace c2014 {
namespace wpilib {

class WpilibInterface {
 public:
  WpilibInterface();

  void WriteActuators();
  void ReadSensors();

 private:
  muan::wpilib::CanWrapper can_;

  muan::wpilib::gyro::GyroReader gyro_;
  DrivetrainInterface drivetrain_;
  SuperStructureInterface superstructure_;
};

}  // namespace wpilib
}  // namespace c2014

#endif  // C2014_WPILIB_WPILIB_INTERFACE_H_
