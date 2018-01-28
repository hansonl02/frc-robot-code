#ifndef C2018_TELEOP_MAIN_H_
#define C2018_TELEOP_MAIN_H_

#include <atomic>
#include "muan/teleop/joystick.h"
#include "muan/wpilib/ds_sender.h"
#include "c2018/subsystems/climber/climber_queues.h"
#include "c2018/subsystems/score_subsystem/score_subsystem_queues.h"
#include "WPILib.h"
#include "muan/queues/queue_manager.h"
#include "muan/wpilib/queue_types.h"
#include "third_party/aos/common/util/phased_loop.h"
#include "third_party/frc971/control_loops/drivetrain/queue_types.h"

namespace c2018 {
namespace teleop {

class TeleopBase {
 public:
  TeleopBase();

  void operator()();
  void Stop();

 private:
  std::atomic<bool> running_;

  // Runs at ~200hz
  void Update();

  void SetReadableLogName();

  void SendDrivetrainMessage();
  void SendScoreSubsystemMessage();
  void SendClimbSubsystemMessage();

  muan::teleop::Joystick throttle_, wheel_;
  muan::teleop::Joystick gamepad_;

  bool high_gear_;
  muan::teleop::Button *shifting_high_, *shifting_low_;
  muan::teleop::Button *quickturn_;

  // Gamepad Buttons
  muan::teleop::Button *first_level_height_, *second_level_height_, *third_level_height_, *score_height;
  muan::teleop::Button *initialize_climb_, *climb_, *godmode_;
  // Gamepad POVs
  muan::teleop::Button *score_back_, *score_front_;
  // Gamepad Axes
  muan::teleop::Button *intake_, *outtake_;
  muan::teleop::Button *godmode_elevator_down_, *godmode_elevator_up_;

      bool god_mode_ = false;

  muan::wpilib::DriverStationSender ds_sender_;

  bool log_name_set_ = false;

  c2018::climber::ClimberGoalProto climber_goal_;
  c2018::score_subsystem::ScoreSubsystemGoalProto score_subsystem_goal_;
};

}  // namespace teleop
}  // namespace c2018

#endif  // C2018_TELEOP_MAIN_H_
