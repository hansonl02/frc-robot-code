#include "c2018/subsystems/climber/climber.h"

namespace c2018 {

namespace climber {

Climber::Climber()
    : goal_reader_{muan::queues::QueueManager<ClimberGoalProto>::Fetch()->MakeReader()},
      input_reader_{muan::queues::QueueManager<ClimberInputProto>::Fetch()->MakeReader()},
      driver_station_{muan::queues::QueueManager<muan::wpilib::DriverStationProto>::Fetch()->MakeReader()} {}

void Climber::Update() {
  bool should_climb = false;
  bool outputs_enabled = false;
  bool batter_output;
  double winch_output;
  ClimberGoal goal;
  ClimberInput input;
  DriverStationStatus ds_status;
  driver_station_.ReadLastMessage();
  if (!goal_reader_.ReadLastMessage(&goal)) {
    // Set default goal values here
  }

  if (input_reader_.ReadLastMessage(&input)) {
    outputs_enabled = ds_status.is_sys_active();
    // use goal here
    switch (goal.climber_goal()) {
      case NONE:
        should_climb = false;
        winch_output = winch_.Update(input.position(), should_climb, outputs_enabled);
        batter_output = batter_.Update(goal.put_down_batter(), outputs_enabled);
        status_proto_->set_climber_state(IDLE);
        break;
      case APPROACHING:
        goal.set_put_down_batter(true);
        batter_output = batter_.Update(goal.put_down_batter(), outputs_enabled);
        status_proto_->set_climber_state(APPROACH);
        break;
      case CLIMBING:
        should_climb = true;
        winch_output = winch_.Update(input.position(), should_climb, outputs_enabled);
        batter_output = batter_.Update(goal.put_down_batter(), outputs_enabled);
        status_proto_->set_climber_state(CLIMB);
        break;
    }

    output_proto->set_release_solenoid(batter_output);
    output_proto->set_voltage(winch_output);
    if (winch_.has_climbed()) {
      status_proto_->set_climber_state(DONE);
    }
    status_queue_->WriteMessage(status_proto_);
    output_queue_->WriteMessage(output_proto_);
  }
}

}  // namespace climber

}  // namespace c2018
