// esp32/arm.h
#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "configuration.h"

class Arm {
public:
    Arm();
    void begin();
    bool moveHome();
    bool moveToPickup();
    bool moveToBin(const String &sizeLabel);
    bool isExtended() const;
    void emergencyStop();

private:
    Servo _servo;
    int _currentAngle;
    volatile bool _busy;
    volatile bool _emergencyFlag;
    bool _moveToAngle(int angle, String &errOut);
};

#endif // ARM_H
