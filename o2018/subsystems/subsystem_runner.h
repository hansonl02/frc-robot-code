#ifndef O2018_SUBSYSTEMS_SUBSYSTEM_RUNNER_H_
#define O2018_SUBSYSTEMS_SUBSYSTEM_RUNNER_H_

#include <atomic>

#include "o2018/subsystems/drivetrain/drivetrain.h"
#include "o2018/subsystems/score_subsystem/score_subsystem.h"
#include "third_party/aos/common/time.h"
#include "third_party/aos/common/util/phased_loop.h"
#include "third_party/aos/linux_code/init.h"

namespace o2018 {
namespace subsystems {

class SubsystemRunner {
 public:
  SubsystemRunner();
  ~SubsystemRunner() = default;
  void operator()();

 private:
  drivetrain::Drivetrain& drivetrain_ = drivetrain::Drivetrain::GetInstance();
  ScoreSubsystem& score_subsystem_ = ScoreSubsystem::GetInstance();
  std::atomic<bool> running_;
};

}  // namespace subsystems
}  // namespace o2018

#endif  // O2018_SUBSYSTEMS_SUBSYSTEM_RUNNER_H_
