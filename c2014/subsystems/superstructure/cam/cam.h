#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_CAM_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_CAM_H_

#include "c2014/subsystems/superstructure/cam/queue_types.h"
#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

namespace cam {

class Cam {
 public:
  Cam() = default;
  CamOutputProto Update(CamInputProto input);
  void SetGoal(CamGoalProto goal);
  bool ready_to_shoot;

 private:
  c2014::cam::CamGoalState cam_goal_;
};

}  // namespace cam

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_CAM_H_
