#include "ground_gear_intake.h"
#include <iostream>

namespace c2017 {

namespace ground_gear_intake {

  GroundGearIntake::GroundGearIntake() {
    double voltage_ = 0.;//creates variable that will later be sent through the queue as roller_voltage 
  }

  double GroundGearIntake::Update(GroundGearIntakeProto input_, GroundGearIntakeGoalProto goal_) {
    Goal ground_intake_goal = goal_->goal();
      if(ground_intake_goal == Goal::CARRY) {
        voltage_ = 0.;
      }
      if(ground_intake_goal == Goal::PICKUP) {
        voltage_ = 12.;
      }
      if(ground_intake_goal == Goal::SCORE) {
        voltage_ = -12.;//outtake
      }
      if (input_->current() > 120) {
       voltage_ = 0.;//stop moving when the motor stalls
      }
    }

}
//end of namespace
}



