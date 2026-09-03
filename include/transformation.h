// esp32/transformation.h
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "configuration.h"

class Transformation {
public:
    Transformation();
    void begin();
    bool fold();
    bool unfold();
    bool stow();  // Return to neutral state
    bool isBusy() const;
    void emergencyStop();

private:
    Servo _servo;
    int _currentAngle;
    volatile bool _busy;
    volatile bool _emergencyFlag;
    bool _moveToAngle(int angle, unsigned long timeout);
};

#endif // TRANSFORMATION_H
