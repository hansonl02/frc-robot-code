#ifndef C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_INTAKES_H_
#define C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_INTAKES_H_

#include "c2014/subsystems/superstructure/intakes/queue_types.h"
#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

namespace intakes {

class Intakes {
 public:
  Intakes() = default;
  IntakesOutputProto Update();
  void SetGoal(const IntakesGoalProto& goal);

 private:
  c2014::intakes::FrontIntakeGoalState front_intake_goal_;
  c2014::intakes::BackIntakeGoalState back_intake_goal_;

  bool front_down_;
  bool back_down_;
};

}  // namespace intakes

}  // namespace c2014

#endif  // C2014_SUBSYSTEMS_SUPERSTRUCTURE_INTAKES_INTAKES_H_
