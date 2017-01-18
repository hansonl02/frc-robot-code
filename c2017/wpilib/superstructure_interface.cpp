#include "c2017/wpilib/superstructure_interface.h"

namespace c2017 {

namespace wpilib {

namespace ports {

namespace superstructure {

//TODO: Kelly figure out the correct ports for everything
constexpr uint32_t kShooterMotorA = 2;
constexpr uint32_t kShooterMotorB = 3;
constexpr uint32_t kShooterMotorC = 4;
constexpr uint32_t kShooterMotorD = 5;

constexpr uint32_t kTriggerMotor = 6;

constexpr uint32_t kBrushMotor = 7;

constexpr uint32_t kBallIntakeMotorA = 8, kBallIntakeMotorB;

constexpr uint32_t kGearIntakeMotor = 9;

constexpr uint32_t kShooterEncoderA = 5, kShooterEncoderB = 6;
constexpr uint32_t kTriggerEncdoerB = 7, kTriggerEncoderB = 8;

constexpr double kMaxVoltage = 12;

} // superstrucute

} // ports

SuperStuctureInterface::SuperstructureInterface() 
    : input_queue_(QueueManager::GetIntastance().superstructure_input_queue()),
      output_queue_(QueueManager::GetInstance().superstructure_output_queue()->MakeReader()), 
      shooter_motor_a_{ports::superstructure::kShooterMotorA}, 
      shooter_motor_b_{ports::superstructure::kShooterMotorB}, 
      shooter_motor_c_{ports::kShooterMotorC}, 
      shooter_motor_d_{ports::superstructure::kShooterMotorD}, 
      trigger_motor_{kTriigerMotor}, 
      brush_motor_{kbrushMotor}, 
      ball_intake_motor_a_{kBallIntakeMotorA}, 
      ball_intake_motor_b_{kBallIntakeMotorB}, 
      gear_intake_motor_{kGearIntakeMotor} {

}

void SuperStructureInterface::ReadSensors() {
  c2017::wpilib::WpilibInputProto sensors;
  constexpr double kMetersPerClick = M_PI * 2.0 * wheel_radius / 360.0;

  sensors->set_shooter_encoder(encoder_left_.Get() * kMetersPerClick);
  sensors->set_trigger_encoder(-encoder_right_.Get() * kMetersPerClick);

  input_queue_->WriteMessage(sensors);
}

void SuperStructureInterface::WriteActuators() {

  auto outputs = output_queue_.ReadLastMessage();
  if (outputs) {
    // Shooter motors
    shooter_motor_a_.Set(
        -muan::utils::Cap((*outputs)->shooter_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    shooter_motor_b_.Set(
        -muan::utils::Cap((*outputs)->shooter_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    shooter_motor_c_.Set(
        -muan::utils::Cap((*outputs)->shooter_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    shooter_motor_d_.Set(
        -muan::utils::Cap((*outputs)->shooter_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);

    // Trigger motor
    trigger_motor_.Set(
        -muan::utils::Cap((*outputs)->trigger_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    
    // Brush motor
    brush_motor_.Set(
        -muan::utils::Cap((*outputs)->brush_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);

    // Main ball intake motors
    ball_intake_motor_a_.Set(
        -muan::utils::Cap((*outputs)->main_intake_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    ball_intake_motor_b_.Set(
        -muan::utils::Cap((*outputs)->main_intake_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);

    // Ground gear intake motor
    gear_intake_motor_.Set(
        -muan::utils::Cap((*outputs)->trigger_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);


  } else {
    motor_left_.Set(0);
    motor_left_.Set(0);
  }
}



} // wpilib

} // c2017
