#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_QUEUE_TYPES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/subsystems/superstructure/cam/cam.pb.h"

namespace c2014 {

namespace cam {

using CamGoalProto = muan::proto::StackProto<::c2014::cam::CamGoal, 256>;
using CamInputProto = muan::proto::StackProto<::c2014::cam::CamInput, 256>;
using CamOutputProto = muan::proto::StackProto<::c2014::cam::CamOutput, 256>;

using CamGoalQueue = muan::queues::MessageQueue<CamGoalProto, 200>;
using CamInputQueue = muan::queues::MessageQueue<CamInputProto, 200>;
using CamOutputQueue = muan::queues::MessageQueue<CamOutputProto, 200>;

}  // namespace cam

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_CAM_QUEUE_TYPES_H_
