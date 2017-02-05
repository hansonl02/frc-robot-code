#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_QUEUE_TYPES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/subsystems/superstructure/stops/stops.pb.h"

namespace c2014 {

namespace stops {

using StopsGoalProto = muan::proto::StackProto<::c2014::stops::StopsGoal, 256>;
using StopsOutputProto = muan::proto::StackProto<::c2014::stops::StopsOutput, 256>;

using StopsGoalQueue = muan::queues::MessageQueue<StopsGoalProto, 200>;
using StopsOutputQueue = muan::queues::MessageQueue<StopsOutputProto, 200>;

}  // namespace stops

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_STOPS_QUEUE_TYPES_H_
