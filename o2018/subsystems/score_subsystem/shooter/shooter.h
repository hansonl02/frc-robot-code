#ifndef O2018_SUBSYSTEMS_SCORE_SUBSYSTEM_SHOOTER_SHOOTER_H_
#define O2018_SUBSYSTEMS_SCORE_SUBSYSTEM_SHOOTER_SHOOTER_H_

namespace o2018 {
namespace score_subsystem {
namespace shooter {

// Intake Voltage constants

constexpr double kSlowOuttakeVoltage = -6;
constexpr double kFastOuttakeVoltage = -9;
constexpr double kIntakeVoltage = 12;

class Shooter {
 public:
  Shooter() = default;
  bool Update(bool has_cube, bool should_punch, bool outputs_enabled);
}

} // namespace shooter
} // namespace score_subsystem
} // namespace o2018

#endif // O2018_SUBSYSTEMS_SCORE_SUBSYSTEM_SHOOTER_SHOOTER_H_
