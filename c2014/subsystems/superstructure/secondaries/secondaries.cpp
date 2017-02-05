#include "c2014/subsystems/superstructure/secondaries/secondaries.h"

namespace c2014 {

namespace secondaries {

SecondariesOutputProto Secondaries::Update() {
  double secondaries_voltage = 0;
  bool secondaries_open = true;

  switch (secondaries_goal_) {
    case IDLE:
      secondaries_voltage = 0;
      secondaries_open = true;
      break;
    case SHOOT:
      secondaries_voltage = 0;
      secondaries_open = true;
      break;
    case SETTLE:
      secondaries_voltage = 12;
      secondaries_open = false;
      break;
    case BARF_BACK:
      secondaries_voltage = -12;
      secondaries_open = false;
      break;
  }

  c2014::secondaries::SecondariesOutputProto output;

  output->set_secondaries_voltage(secondaries_voltage);
  output->set_secondaries_open(secondaries_open);

  return output;
}

void Secondaries::SetGoal(SecondariesGoalProto goal) {
  secondaries_goal_ = goal->secondaries_goal();
}

}  // namespace secondaries

}  // namespace c2014
