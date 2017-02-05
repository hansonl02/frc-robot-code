#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_STOPS_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_STOPS_H_

#include "c2014/subsystems/superstructure/stops/queue_types.h"
#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

namespace stops {

class Stops {
 public:
  Stops() = default;
  StopsOutputProto Update();
  void SetGoal(StopsGoalProto goal);

 private:
  bool short_shot_;
};

}  // namespace stops

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_STOPS_H_
