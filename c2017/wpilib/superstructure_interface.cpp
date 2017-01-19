#include "c2017/wpilib/superstructure_interface.h"

namespace c2017 {

namespace wpilib {

namespace ports {

namespace superstructure {

//TODO: Kelly figure out the correct ports for everything
// Motor ports
constexpr uint32_t kShooterMotorA = 2;
constexpr uint32_t kShooterMotorB = 3;
constexpr uint32_t kShooterMotorC = 4;
constexpr uint32_t kShooterMotorD = 5;

constexpr uint32_t kTriggerMotor = 6;

constexpr uint32_t kBrushMotor = 7;

constexpr uint32_t kBallIntakeMotorA = 8, kBallIntakeMotorB = 9;

constexpr uint32_t kGearIntakeMotor = 10;

// Sensor ports
constexpr uint32_t kShooterEncoderA = 5, kShooterEncoderB = 6;
constexpr uint32_t kTriggerEncoderA = 7, kTriggerEncoderB = 8;

// Solenoid ports
constexpr uint32_t kBallIntakeSolenoid = 1;
constexpr uint32_t kGroundGearIntakeSolenoid = 2;
constexpr uint32_t kGearShutterSolenoid = 3;
constexpr uint32_t kHpGearIntakeSolenoid = 4;
constexpr uint32_t kMagazineSolenoid = 5;

// Other
constexpr double kMaxVoltage = 12;

} // superstrucute

} // ports

SuperStructureInterface::SuperStructureInterface(muan::wpilib::CanWrapper* can_wrapper) 
    : input_queue_(QueueManager::GetInstance().superstructure_input_queue()),
      output_queue_(QueueManager::GetInstance().superstructure_output_queue()->MakeReader()), 
      shooter_motor_a_{ports::superstructure::kShooterMotorA}, 
      shooter_motor_b_{ports::superstructure::kShooterMotorB}, 
      shooter_motor_c_{ports::superstructure::kShooterMotorC}, 
      shooter_motor_d_{ports::superstructure::kShooterMotorD}, 
      trigger_motor_{ports::superstructure::kTriggerMotor}, 
      brush_motor_{ports::superstructure::kBrushMotor}, 
      ball_intake_motor_a_{ports::superstructure::kBallIntakeMotorA}, 
      ball_intake_motor_b_{ports::superstructure::kBallIntakeMotorB}, 
      gear_intake_motor_{ports::superstructure::kGearIntakeMotor}, 
      shooter_encoder_{ports::superstructure::kShooterEncoderA, ports::superstructure::kShooterEncoderB},
      trigger_encoder_{ports::superstructure::kTriggerEncoderA, ports::superstructure::kTriggerEncoderB}, 
      pcm_{can_wrapper->pcm()} {
  
  pcm_->CreateSolenoid(ports::superstructure::kBallIntakeSolenoid);
  pcm_->CreateSolenoid(ports::superstructure::kGroundGearIntakeSolenoid);
  pcm_->CreateSolenoid(ports::superstructure::kGearShutterSolenoid);
  pcm_->CreateSolenoid(ports::superstructure::kHpGearIntakeSolenoid);
  pcm_->CreateSolenoid(ports::superstructure::kMagazineSolenoid);

}

void SuperStructureInterface::ReadSensors() {
  c2017::wpilib::WpilibInputProto sensors;
  constexpr double kRadiansPerClick = M_PI * 2  / 360.0;

  sensors->set_shooter_encoder(shooter_encoder_.Get() * kRadiansPerClick);
  sensors->set_trigger_encoder(trigger_encoder_.Get() * kRadiansPerClick);

  auto current_reader = QueueManager::GetInstance().pdp_status_queue().MakeReader().ReadLastMessage();

  if (current_reader) {
    // Place holder for now
    // TODO: Kelly figure out what exactly needs current inputs and what ports it is in
    // Ground gear intake, climber
    sensors->set_ground_gear_current((*current_reader)->current4()); 
    sensors->set_climber_current((*current_reader)->current5()); 
  }

  input_queue_->WriteMessage(sensors);
}

void SuperStructureInterface::WriteActuators() {

  auto outputs = output_queue_.ReadLastMessage();
  auto current_reader = QueueManager::GetInstance().pdp_status_queue().MakeReader().ReadLastMessage();
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
        -muan::utils::Cap((*outputs)->main_roller_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);
    ball_intake_motor_b_.Set(
        -muan::utils::Cap((*outputs)->main_roller_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);

    // Ground gear intake motor
    gear_intake_motor_.Set(
        -muan::utils::Cap((*outputs)->trigger_voltage(), -ports::superstructure::kMaxVoltage, ports::superstructure::kMaxVoltage) /
        12.0);

    // Solenoids 
    pcm_->WriteSolenoid(ports::superstructure::kBallIntakeSolenoid, (*outputs)->ball_intake_down());
    pcm_->WriteSolenoid(ports::superstructure::kGroundGearIntakeSolenoid, (*outputs)->ground_gear_down());
    pcm_->WriteSolenoid(ports::superstructure::kGearShutterSolenoid, (*outputs)->gear_shutter_open());
    pcm_->WriteSolenoid(ports::superstructure::kHpGearIntakeSolenoid, (*outputs)->hp_gear_open());
    pcm_->WriteSolenoid(ports::superstructure::kMagazineSolenoid, (*outputs)->magazine_open());

  } else {
    shooter_motor_a_.Set(0);
    shooter_motor_b_.Set(0);
    shooter_motor_c_.Set(0);
    shooter_motor_d_.Set(0);
    
    trigger_motor_.Set(0);

    brush_motor_.Set(0);
    ball_intake_motor_a_.Set(0);
    ball_intake_motor_b_.Set(0);
    gear_intake_motor_.Set(0);

    pcm_->WriteSolenoid(ports::superstructure::kBallIntakeSolenoid, false);
    pcm_->WriteSolenoid(ports::superstructure::kGroundGearIntakeSolenoid, false);
    pcm_->WriteSolenoid(ports::superstructure::kGearShutterSolenoid, false);
    pcm_->WriteSolenoid(ports::superstructure::kHpGearIntakeSolenoid, false);
    pcm_->WriteSolenoid(ports::superstructure::kMagazineSolenoid, false);
  }
}



} // wpilib

} // c2017
