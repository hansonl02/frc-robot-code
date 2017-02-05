#include "c2014/subsystems/superstructure/cam/cam.h"

namespace c2014 {

namespace cam {

CamOutputProto Cam::Update(CamInputProto input) {
  ready_to_shoot = input->ready_to_shoot();
  double cam_voltage = 0;

  switch (cam_goal_) {
    case CAM_IDLE:
      cam_voltage = 0;
      break;
    case CAM_PREPARE:
      if (!(input->ready_to_shoot())) {
        cam_voltage = 3; // hope this works
      } else {
        cam_voltage = 0;
      }
      break;
    case CAM_SHOOT:
      cam_voltage = 5; // hope this works
      break;
  }

  c2014::cam::CamOutputProto output;

  output->set_cam_voltage(cam_voltage);

  return output;
}

void Cam::SetGoal(CamGoalProto goal) {
  cam_goal_ = goal->cam_goal();
}

}  // namespace cam

}  // namespace c2014
