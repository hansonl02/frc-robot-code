#include "c2014/queue_manager/queue_manager.h"

namespace c2014 {

QueueManager& QueueManager::GetInstance() {
  static QueueManager instance;
  return instance;
}

MessageQueue<muan::proto::StackProto<PdpStatus, 512>>& QueueManager::pdp_status_queue() {
  return pdp_status_queue_;
}

muan::wpilib::DriverStationQueue* QueueManager::driver_station_queue() { return &driver_station_queue_; }

frc971::control_loops::drivetrain::InputQueue* QueueManager::drivetrain_input_queue() {
  return &drivetrain_input_queue_;
}

frc971::control_loops::drivetrain::GoalQueue* QueueManager::drivetrain_goal_queue() {
  return &drivetrain_goal_queue_;
}

frc971::control_loops::drivetrain::StatusQueue* QueueManager::drivetrain_status_queue() {
  return &drivetrain_status_queue_;
}

frc971::control_loops::drivetrain::OutputQueue* QueueManager::drivetrain_output_queue() {
  return &drivetrain_output_queue_;
}

c2014::wpilib::WpilibOutputQueue& QueueManager::superstructure_output_queue() {
  return superstructure_output_queue_;
}

// Intakes Queues
c2014::intakes::IntakesStatusQueue& QueueManager::intakes_status_queue() { return intakes_status_queue(); }

// Cam Queues
c2014::cam::CamInputQueue& QueueManager::cam_input_queue() { return cam_input_queue_; }

}  // namespace c2014
