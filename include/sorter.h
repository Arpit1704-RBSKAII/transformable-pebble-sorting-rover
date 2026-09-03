// esp32/sorter.h
#ifndef SORTER_H
#define SORTER_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "configuration.h"

class Sorter {
public:
    Sorter();
    void begin();
    bool sortToBin(const String &sizeLabel);
    bool stow();
    bool isBusy() const;
    void emergencyStop();

private:
    Servo _servo;
    int _currentAngle;
    volatile bool _busy;
    volatile bool _emergencyFlag;
    bool _moveToAngle(int angle, unsigned long timeout);
};

#endif // SORTER_H
