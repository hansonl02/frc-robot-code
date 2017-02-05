#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_SECONDARIES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_SECONDARIES_H_

#include "c2014/subsystems/superstructure/secondaries/queue_types.h"
#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

namespace secondaries {

class Secondaries {
 public:
  Secondaries() = default;
  SecondariesOutputProto Update();
  void SetGoal(SecondariesGoalProto goal);

 private:
  c2014::secondaries::SecondariesGoalState secondaries_goal_;
};

}  // namespace secondaries

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_SECONDARIES_H_
