#include "c2014/subsystems/superstructure/fingers/fingers.h"

namespace c2014 {

namespace fingers {

FingersOutputProto Fingers::Update() {
  bool close_upper_fingers = false; 
  bool close_lower_fingers = false; 

  switch (fingers_goal) {
  case SHORT:
    //shoot high but not far
    close_upper_fingers = false;
    close_lower_fingers = true;
    break;
  case LONG:
    //shoot far but low
    close_upper_fingers = true;
    close_lower_fingers = false;
    break;
  case INTAKING:
    //open fingers so a ball can settle in
    close_upper_fingers = false;
    close_lower_fingers = false;
    break;
  }

  c2014::fingers::FingersOutputProto output;

  output->set_close_upper_fingers(close_upper_fingers);
  output->set_close_lower_fingers(close_lower_fingers);

  return output;
}

void Fingers::SetGoal(FingersGoalProto goal) {
  fingers_goal = goal->fingers_goal();
}

} // namespace fingers

} // namespace c2014
