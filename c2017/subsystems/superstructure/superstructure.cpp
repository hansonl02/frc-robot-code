#include "c2017/subsystems/superstructure/superstructure.h"

namespace c2017 {

namespace superstructure {

SuperStructure::SuperStructure(c2017::intake_group::IntakeGroupGoalQueue* intake_group_goal_queue,
    c2017::shooter_group::ShooterGroupGoalQueue* shooter_group_goal_queue,
    c2017::climber::ClimberGoalQueue* climber_goal_queue,
    c2017::shooter::ShooterInputQueue* shooter_input_queue,
    c2017::trigger::TriggerInputQueue* trigger_input_queue,
    c2017::magazine::MagazineInputQueue* magazine_input_queue,
    c2017::ground_gear_intake::GroundGearIntakeInputQueue* ground_gear_input_queue,
    c2017::ball_intake::BallIntakeInputQueue* ball_intake_input_queue,
    c2017::climber::ClimberInputQueue* climber_input_queue,
    muan::wpilib::DriverStationQueue* driver_station_queue)  {

}

void SuperStructure::Update() {

}


}

}
