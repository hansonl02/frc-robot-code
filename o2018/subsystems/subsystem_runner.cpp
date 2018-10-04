#include "o2018/subsystems/subsystem_runner.h"
#include "WPILib.h"
#include "muan/utils/threading_utils.h"

namespace o2018 {
namespace subsystems {

SubsystemRunner::SubsystemRunner() {}

void SubsystemRunner::operator()() {
  aos::time::PhasedLoop phased_loop(std::chrono::milliseconds(10));
  aos::SetCurrentThreadRealtimePriority(50);
  muan::utils::SetCurrentThreadName("SubsystemRunner");

  running_ = true;

  while (running_) {
    // bool outputs_enabled = RobotController::IsSysActive();
    // drivetrain_.Update(outputs_enabled);
    // score_subsystem_.Update(outputs_enabled);

    phased_loop.SleepUntilNext();
  }
}

}  // namespace subsystems
}  // namespace o2018
