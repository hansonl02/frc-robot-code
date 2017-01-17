#ifndef C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUND_GEAR_INTAKE_H_
#define C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUND_GEAR_INTAKE_H_

#include "queue_types.h"

namespace c2017 {

namespace ground_gear_intake {

class GroundGearIntake {
 public:
  GroundGearIntake();
  GroundGearIntakeOutputProto Update(GroundGearIntakeInputProto input);
  void SetGoal(GroundGearIntakeGoalProto goal);
 private:
  GroundGearIntakeGoalProto goal_;
};

} // ground_gear_intake
  // c2017
}
#endif //C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUNDGEARINTAKE_H_
