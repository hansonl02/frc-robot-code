#include "ground_gear_intake.h"
#include <iostream>

namespace c2017 {

namespace ground_gear_intake {

  GroundGearIntake::GroundGearIntake() {
    double voltage_ = 0.;//creates variable that will later be sent through the queue as roller_voltage 
    void GroundGearIntake::SetGoal() {
      //stuff
    }
    double GroundGearIntake::Update(GroundGearIntakeInput input_, GroundGearIntakeGoal goal_) {
      ground_intake_goal = goal_->goal();
    if(ground_intake_goal == Goal::CARRY) {
      voltage_ = 0.;
      
    }
    voltage_ = 12;
      if (current > 80) {
        voltage_ = 0.;//stop moving when the motor stalls
      }

    }

  }
//end of namespace
}



