<<<<<<< HEAD
#ifndef C2017_WPILIB_QUEUE_TYPES_H
#define C2017_WPILIB_QUEUE_TYPES_H
=======
#ifndef C2017_WPILIB_QUEUE_TYPES_H_
#define C2017_WPILIB_QUEUE_TYPES_H_
>>>>>>> upstream/master

#include "muan/proto/stack_proto.h"
#include "muan/queues/message_queue.h"
#include "c2017/wpilibwpilib.pb.h"

namespace c2017 {

namespace wpilib {
<<<<<<< HEAD
  
  using WpilibOutputProto = muan::proto::StackProto<WpilibOutput, 1024>;

  using WpilibOutputQueue = muan::queues::MessageQueue<WpilibOutputProto, 1024>; 
=======

  using WpilibOutputProto = muan::proto::StackProto<WpilibOutput, 1024>;

  using WpilibOutputQueue = muan::queues::MessageQueue<WpilibOutputProto, 1024>;
>>>>>>> upstream/master

} // wpilib

} // c2017

<<<<<<< HEAD
#endif 
=======
#endif
>>>>>>> upstream/master
