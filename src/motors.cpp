// esp32/motors.cpp
#include "motors.h"

Motors::Motors() : _currentLeftSpeed(0), _currentRightSpeed(0), _moving(false), _emergencyFlag(false) {}

void Motors::begin() {
    pinMode(MOTOR_LEFT_PWM_PIN, OUTPUT);
    pinMode(MOTOR_LEFT_DIR_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR_PIN, OUTPUT);
    
    digitalWrite(MOTOR_LEFT_DIR_PIN, LOW);
    digitalWrite(MOTOR_RIGHT_DIR_PIN, LOW);
    analogWrite(MOTOR_LEFT_PWM_PIN, 0);
    analogWrite(MOTOR_RIGHT_PWM_PIN, 0);
    
#if ENABLE_DEBUG_PRINTS
    Serial.println("[MOTORS] Initialized");
#endif
}

void Motors::_setMotorSpeed(int leftSpeed, int rightSpeed) {
    if (_emergencyFlag) return;
    
    _currentLeftSpeed = constrain(leftSpeed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
    _currentRightSpeed = constrain(rightSpeed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
    
    // Left motor
    if (_currentLeftSpeed >= 0) {
        digitalWrite(MOTOR_LEFT_DIR_PIN, HIGH);
        analogWrite(MOTOR_LEFT_PWM_PIN, _currentLeftSpeed);
    } else {
        digitalWrite(MOTOR_LEFT_DIR_PIN, LOW);
        analogWrite(MOTOR_LEFT_PWM_PIN, -_currentLeftSpeed);
    }
    
    // Right motor
    if (_currentRightSpeed >= 0) {
        digitalWrite(MOTOR_RIGHT_DIR_PIN, HIGH);
        analogWrite(MOTOR_RIGHT_PWM_PIN, _currentRightSpeed);
    } else {
        digitalWrite(MOTOR_RIGHT_DIR_PIN, LOW);
        analogWrite(MOTOR_RIGHT_PWM_PIN, -_currentRightSpeed);
    }
}

void Motors::moveForward(int speed) {
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, MOTOR_MAX_SPEED);
    _setMotorSpeed(pwm, pwm);
    _moving = true;
}

void Motors::moveBackward(int speed) {
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, MOTOR_MAX_SPEED);
    _setMotorSpeed(-pwm, -pwm);
    _moving = true;
}

void Motors::turnLeft(int speed) {
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, MOTOR_MAX_SPEED);
    _setMotorSpeed(pwm / 2, pwm);  // Reduce left motor speed
    _moving = true;
}

void Motors::turnRight(int speed) {
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, MOTOR_MAX_SPEED);
    _setMotorSpeed(pwm, pwm / 2);  // Reduce right motor speed
    _moving = true;
}

void Motors::stop() {
    _setMotorSpeed(0, 0);
    _moving = false;
}

bool Motors::isMoving() const {
    return _moving && !_emergencyFlag;
}

void Motors::emergencyStop() {
    _emergencyFlag = true;
    stop();
}
