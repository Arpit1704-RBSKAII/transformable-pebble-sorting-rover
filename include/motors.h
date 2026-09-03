// esp32/motors.h
#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "configuration.h"

class Motors {
public:
    Motors();
    void begin();
    void moveForward(int speed = 100);
    void moveBackward(int speed = 100);
    void turnLeft(int speed = 80);
    void turnRight(int speed = 80);
    void stop();
    bool isMoving() const;
    void emergencyStop();

private:
    void _setMotorSpeed(int leftSpeed, int rightSpeed);
    void _enableMotors();
    void _disableMotors();
    
    int _currentLeftSpeed;
    int _currentRightSpeed;
    volatile bool _moving;
    volatile bool _emergencyFlag;
};

#endif // MOTORS_H
