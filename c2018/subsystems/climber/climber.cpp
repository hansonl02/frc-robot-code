#include "c2018/subsystems/climber/climber.h"

namespace c2018 {

namespace climber {

Climber::Climber()
    : goal_reader_{muan::queues::QueueManager<ClimberGoalProto>::Fetch()->MakeReader()},
      input_reader_{muan::queues::QueueManager<ClimberInputProto>::Fetch()->MakeReader()},
      ds_status_{muan::queues::QueueManager<muan::wpilib::DriverStationProto>::Fetch()->MakeReader()} {}

void Climber::Update() {
  bool should_climb = false;
  bool outputs_enabled = false;
  bool batter_output;
  double winch_output;

  ClimberStatusProto status_proto;
  ClimberOutputProto output_proto;
  ClimberGoalProto goal_proto;

  ClimberGoal goal;
  ClimberInput input;

  if (!goal_reader_.ReadLastMessage()) {
    goal_proto->set_climber_goal(NONE);
  }

  if (input_reader_.ReadLastMessage()) {
    outputs_enabled = ds_status_.ReadLastMessage().value()->is_sys_active();
    // use goal here
    switch (goal.climber_goal()) {
      case NONE:
        should_climb = false;
        status_proto->set_climber_state(IDLE);
        break;
      case APPROACHING:
        goal.set_put_down_batter(true);
        status_proto->set_climber_state(APPROACH);
        break;
      case CLIMBING:
        should_climb = true;
        status_proto->set_climber_state(CLIMB);
        break;
    }

    winch_output = winch_.Update(&status_proto, input.position(), should_climb, outputs_enabled);
    batter_output = batter_.Update(goal.put_down_batter(), outputs_enabled);

    output_proto->set_release_solenoid(batter_output);
    output_proto->set_voltage(winch_output);

    if (winch_.has_climbed()) {
      status_proto->set_climber_state(DONE);
    }

    status_queue_->WriteMessage(status_proto);
    output_queue_->WriteMessage(output_proto);
  }
}

}  // namespace climber

}  // namespace c2018
