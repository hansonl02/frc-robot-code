#include "c2018/subsystems/climber/climber.h"

namespace c2018 {

namespace climber {

Climber::Climber() : goal_reader_ { QueueManager<ClimbGoal>::Fetch()->MakeReader(); }
{}

void Climber::Update() {
  bool should_climb = false;
  ClimbGoal goal;

  if (goal_reader_.ReadLastMessage(&goal)) {
    // use goal here
    switch (Goal) {
      case NONE:
        should_climb = false;
        Winch::Update(encoder, should_climb, outputs_enabled);
        Batter::Update(should_release, outputs_enabled);
      case CLIMBING:
        should_climb = true;
        Winch::Update(encoder, should_climb, outputs_enabled);
        Batter::Update(should_release, outputs_enabled);
    }
  }
}

}  // namespace climber

}  // namespace c2018