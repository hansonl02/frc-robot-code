#include "c2014/subsystems/superstructure/stops/stops.h"

namespace c2014 {

namespace stops {

StopsOutputProto Stops::Update() {
  bool short_shot = short_shot_;
  //solenoid extends to block catapult early and shorten shot
  c2014::stops::StopsOutputProto output;

  output->set_short_shot(short_shot);

  return output;
}

void Stops::SetGoal(StopsGoalProto goal) {
  short_shot_ = goal->short_shot();
}

}  // namespace stops

}  // namespace c2014
