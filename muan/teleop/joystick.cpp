#include "muan/teleop/joystick.h"
#include "muan/teleop/button.h"

namespace muan {

namespace teleop {

Joystick::Joystick(int32_t port) : queue_{nullptr}, wpilib_joystick_{port} {}

Joystick::Joystick(int32_t port, JoystickStatusQueue* queue) : queue_{queue}, wpilib_joystick_{port} {}

::Joystick* Joystick::wpilib_joystick() { return &wpilib_joystick_; }

Button* Joystick::MakeButton(uint32_t button_id) {
  buttons_.emplace_back(new muan::teleop::Button(this, button_id));
  return buttons_[buttons_.size() - 1].get();
}

muan::teleop::Button* Joystick::MakePov(uint32_t button, Pov position) {
  buttons_.emplace_back(new muan::teleop::PovButton(this, button, position));
  return buttons_[buttons_.size() - 1].get();
}

muan::teleop::Button* Joystick::MakeAxis(uint32_t button) {
  buttons_.emplace_back(new muan::teleop::AxisButton(this, button, .7));
  return buttons_[buttons_.size() - 1].get();
}

void Joystick::Update() {
  for (auto& button : buttons_) {
    button->Update();
  }
  if (queue_) {
    LogButtons();
  }
}

void Joystick::LogButtons() {
  JoystickStatusProto joystick_status;
  joystick_status->set_button1(wpilib_joystick()->GetRawButton(1));
  joystick_status->set_button2(wpilib_joystick()->GetRawButton(2));
  joystick_status->set_button3(wpilib_joystick()->GetRawButton(3));
  joystick_status->set_button4(wpilib_joystick()->GetRawButton(4));
  joystick_status->set_button5(wpilib_joystick()->GetRawButton(5));
  joystick_status->set_button6(wpilib_joystick()->GetRawButton(6));
  joystick_status->set_button7(wpilib_joystick()->GetRawButton(7));
  joystick_status->set_button8(wpilib_joystick()->GetRawButton(8));
  joystick_status->set_button9(wpilib_joystick()->GetRawButton(9));
  joystick_status->set_button10(wpilib_joystick()->GetRawButton(10));
  joystick_status->set_button11(wpilib_joystick()->GetRawButton(11));
  joystick_status->set_button12(wpilib_joystick()->GetRawButton(12));

  joystick_status->set_axis1(wpilib_joystick_.GetRawAxis(1));
  joystick_status->set_axis2(wpilib_joystick_.GetRawAxis(2));
  joystick_status->set_axis3(wpilib_joystick_.GetRawAxis(3));
  joystick_status->set_axis4(wpilib_joystick_.GetRawAxis(4));
  joystick_status->set_axis5(wpilib_joystick_.GetRawAxis(5));

  queue_->WriteMessage(joystick_status);
}

}  // namespace teleop
}  // namespace muan
