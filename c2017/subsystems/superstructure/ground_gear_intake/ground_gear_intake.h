#ifndef C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUNDGEARINTAKE_H_
#define C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUNDGEARINTAKE_H_

#include "queue_types.h"

namespace c2017 {

namespace ground_gear_intake {

  class GroundGearIntake {
   public:
    double voltage_;
    auto Update();
  }

} // ground_gear_intake

}
#endif //C2017_SUBSYSTEMS_SUPERSTRUCTURE_GROUNDGEARINTAKE_H_
