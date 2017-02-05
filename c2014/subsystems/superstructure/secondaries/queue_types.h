#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_QUEUE_TYPES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/subsystems/superstructure/secondaries/secondaries.pb.h"

namespace c2014 {

namespace secondaries {

using SecondariesGoalProto = muan::proto::StackProto<::c2014::secondaries::SecondariesGoal, 256>;
using SecondariesOutputProto = muan::proto::StackProto<::c2014::secondaries::SecondariesOutput, 256>;

using SecondariesGoalQueue = muan::queues::MessageQueue<SecondariesGoalProto, 200>;
using SecondariesOutputQueue = muan::queues::MessageQueue<SecondariesOutputProto, 200>;

}  // namespace secondaries

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_SECONDARIES_QUEUE_TYPES_H_
