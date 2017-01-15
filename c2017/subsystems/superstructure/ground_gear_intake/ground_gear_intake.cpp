#include "ground_gear_intake.h"
#include <iostream>

namespace c2017 {

namespace ground_gear_intake {

GroundGearIntake::GroundGearIntake() {}
double voltage = 0;
bool is_solenoid_up = true;

GroundGearIntakeOutputProto GroundGearIntake::Update(GroundGearIntakeInputProto input) {
  auto ground_intake_goal = goal_->goal();
  double voltage = 0;
  if(ground_intake_goal == GroundGearIntakeGoal::CARRY) {
    voltage = 0.;
		is_solenoid_up = true;
  }
  if(ground_intake_goal == GroundGearIntakeGoal::PICKUP) {
    voltage = 12.;
		is_solenoid_up = false;
  }
  if(ground_intake_goal == GroundGearIntakeGoal::SCORE) {
    voltage = -12.;//outtake
		is_solenoid_up = false;
  }
  if (input->current() > 120) {//don't do bang bang, go into pickup when motor stalls
    voltage = 0.;//stop moving when the motor stalls
    is_solenoid_up = true;
   }
  GroundGearIntakeOutputProto output;
  output->set_roller_voltage(voltage);
  output->set_solenoid(is_solenoid_up);
  return output;

}


}
//end of namespace
}



