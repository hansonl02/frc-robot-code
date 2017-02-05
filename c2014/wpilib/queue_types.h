#ifndef C2014_WPILIB_QUEUE_TYPES_H_
#define C2014_WPILIB_QUEUE_TYPES_H_

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2014/wpilib/wpilib_superstructure.pb.h"

namespace c2014 {

namespace wpilib {

using WpilibOutputProto = muan::proto::StackProto<WpilibOutput, 1024>;

using WpilibOutputQueue = muan::queues::MessageQueue<WpilibOutputProto, 1024>;

}  // namespace wpilib

}  // namespace c2014

#endif  // C2014_WPILIB_QUEUE_TYPES_H_
