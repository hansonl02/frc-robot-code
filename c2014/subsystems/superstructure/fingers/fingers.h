#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_FINGERS_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_FINGERS_H_

#include "c2014/subsystems/superstructure/fingers/queue_types.h"
#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

namespace fingers {

class Fingers {
 public:
  Fingers() = default;
  FingersOutputProto Update();
  void SetGoal(FingersGoalProto goal);

 private:
  c2014::fingers::FingersGoalState fingers_goal;
};

}  // namespace fingers

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_FINGERS_H_
