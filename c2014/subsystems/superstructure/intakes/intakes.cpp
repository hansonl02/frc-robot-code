#include "c2014/subsystems/superstructure/intakes/intakes.h"

namespace c2014 {

namespace intakes {

IntakesOutputProto Intakes::Update() {
  double front_intake_voltage = 0;
  double back_intake_voltage = 0;
  bool front_down = false;
  bool back_down = false;

  switch (front_intake_goal_) {
    case FRONT_IDLE:
      front_intake_voltage = 0;
      break;
    case FRONT_INTAKE:
      front_intake_voltage = 12;
      break;
    case FRONT_OUTTAKE:
      front_intake_voltage = -12;
      break;
  }

  switch (back_intake_goal_) {
    case BACK_IDLE:
      back_intake_voltage = 0;
      break;
    case BACK_INTAKE:
      back_intake_voltage = 12;
      break;
    case BACK_OUTTAKE:
      back_intake_voltage = -12;
      break;
  }

  c2014::intakes::IntakesOutputProto output;

  output->set_front_intake_voltage(front_intake_voltage);
  output->set_back_intake_voltage(back_intake_voltage);
  output->set_front_down(front_down);
  output->set_back_down(back_down);

  return output;
}

void Intakes::SetGoal(const IntakesGoalProto& goal) {
  front_down_ = goal->front_down();
  back_down_ = goal->back_down();
  front_intake_goal_ = goal->front_intake_goal();
  back_intake_goal_ = goal->back_intake_goal();
}

}  // namespace intakes

}  // namespace c2014
