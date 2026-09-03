// esp32/gripper.cpp
#include "gripper.h"

Gripper::Gripper() : _angle(GRIPPER_OPEN_ANGLE), _emergencyFlag(false) {}

void Gripper::begin() {
    _servo.setPeriodHertz(50);
    _servo.attach(GRIPPER_SERVO_PIN, 500, 2400);
    _servo.write(_angle);
    delay(150);
#if ENABLE_DEBUG_PRINTS
    Serial.println("[GRIPPER] Initialized");
#endif
}

bool Gripper::open() {
    if (_emergencyFlag) return false;
    _servo.write(GRIPPER_OPEN_ANGLE);
    _angle = GRIPPER_OPEN_ANGLE;
    delay(GRIPPER_STEP_DELAY_MS * 5);
    return true;
}

bool Gripper::close() {
    if (_emergencyFlag) return false;
    _servo.write(GRIPPER_CLOSE_ANGLE);
    _angle = GRIPPER_CLOSE_ANGLE;
    delay(GRIPPER_STEP_DELAY_MS * 5);
    return true;
}

bool Gripper::isClosed() const {
    return _angle == GRIPPER_CLOSE_ANGLE;
}

void Gripper::emergencyStop() {
    _emergencyFlag = true;
    _servo.detach();
}
