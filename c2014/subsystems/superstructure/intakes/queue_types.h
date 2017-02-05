#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_QUEUE_TYPES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/subsystems/superstructure/intakes/intakes.pb.h"

namespace c2014 {

namespace intakes {

using IntakesOutputProto = muan::proto::StackProto<IntakesOutput, 256>;
using IntakesStatusProto = muan::proto::StackProto<IntakesStatus, 256>;
using IntakesGoalProto = muan::proto::StackProto<IntakesGoal, 256>;

using IntakesStatusQueue = muan::queues::MessageQueue<IntakesStatusProto, 100>;

}  // namespace intakes

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_QUEUE_TYPES_H_
