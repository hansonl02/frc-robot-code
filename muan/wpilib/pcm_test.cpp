#include <WPILib.h>
#include "can_wrapper.h"
#include "third_party/aos/common/time.h"
#include "third_party/aos/common/util/phased_loop.h"

class BuildTestRobot : public RobotBase {
 public:
  void StartCompetition() override {
    muan::wpilib::PdpWrapper::Queue pdp_queue;
    muan::wpilib::CanWrapper can{&pdp_queue};
    std::thread can_thread{std::ref(can)};

    aos::time::PhasedLoop loop{std::chrono::milliseconds(10)};

    can.pcm()->CreateSolenoid(6);

    HAL_ObserveUserProgramStarting();

    while (true) {
      if (IsDisabled()) {
        can.pcm()->WriteSolenoid(6, false);
        HAL_ObserveUserProgramDisabled();
      } else if (IsAutonomous()) {
        can.pcm()->WriteSolenoid(6, true);
        HAL_ObserveUserProgramAutonomous();
      }
    }
  }
};

START_ROBOT_CLASS(BuildTestRobot);
