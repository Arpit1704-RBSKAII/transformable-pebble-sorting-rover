// esp32/gripper.h
#ifndef GRIPPER_H
#define GRIPPER_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "configuration.h"

class Gripper {
public:
    Gripper();
    void begin();
    bool open();
    bool close();
    bool isClosed() const;
    void emergencyStop();

private:
    Servo _servo;
    int _angle;
    volatile bool _emergencyFlag;
};

#endif // GRIPPER_H
