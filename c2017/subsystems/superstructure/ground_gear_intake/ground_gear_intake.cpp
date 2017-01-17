#include "ground_gear_intake.h"
#include <iostream>

namespace c2017 {

namespace ground_gear_intake {
  
  bool is_solenoid_up_ = false; //will lift when intake stalls
  bool has_current_spiked_ = false;

GroundGearIntake::GroundGearIntake() {
  is_solenoid_up_ = false; //will lift when intake stalls
  has_current_spiked_ = false;
}

GroundGearIntakeOutputProto GroundGearIntake::Update(GroundGearIntakeInputProto input) {
  auto ground_intake_goal = goal_->goal();
  double voltage = 0;
  
  if(ground_intake_goal == GroundGearIntakeGoal::CARRY) {
    voltage = 0;
    is_solenoid_up_ = true;
    has_current_spiked_ = false;
  }
  
  if(ground_intake_goal == GroundGearIntakeGoal::PICKUP) {
    voltage = 12;
    is_solenoid_up_ = false;
    if (input->current() > 120) { //the intake stalls when its current spikes
      has_current_spiked_ = true; 
    }
    if (has_current_spiked_) {
      voltage = 0; //stop moving when the motor stalls
      is_solenoid_up_ = true;
    }
  }
  
  if(ground_intake_goal == GroundGearIntakeGoal::SCORE) {
    voltage = -12; //outtake
    is_solenoid_up_ = true;
    has_current_spiked_ = false;
  } //sends voltage and solenoid output
  
  GroundGearIntakeOutputProto output;
  output->set_roller_voltage(voltage);
  output->set_solenoid(!is_solenoid_up_);
  return output;
}

void GroundGearIntake::SetGoal(GroundGearIntakeGoalProto goal) {
  goal_ = goal;
}

}//ground_gear_intake

}//c2017



