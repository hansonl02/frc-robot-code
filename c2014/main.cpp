#include <WPILib.h>
#include "c2014/wpilib_update/main.h"
#include "subsystems/subsystem_runner.h"

class WpilibRobot : public IterativeRobot {
 public:
  WpilibRobot() { c2014::QueueManager::GetInstance().StartLogging(); }

  void TeleopPeriodic() override { main_.Update(); }

  void AutonomousPeriodic() override { main_.Update(); }

 private:
  c2014::SubsystemRunner subsystem_runner_;
  std::thread subsystem_thread{std::ref(subsystem_runner_)};

  c2014::citrus_robot::CitrusRobot main_;
};

START_ROBOT_CLASS(WpilibRobot);
