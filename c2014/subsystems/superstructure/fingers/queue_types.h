#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_QUEUE_TYPES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/subsystems/superstructure/fingers/fingers.pb.h"

namespace c2014 {

namespace fingers {

using FingersGoalProto = muan::proto::StackProto<FingersGoal, 256>;
using FingersOutputProto = muan::proto::StackProto<FingersOutput, 256>;

}  // namespace fingers

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_FINGERS_QUEUE_TYPES_H_
