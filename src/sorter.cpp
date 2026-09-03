// esp32/sorter.cpp
#include "sorter.h"

Sorter::Sorter() : _currentAngle(SORTER_ANGLE_STOW), _busy(false), _emergencyFlag(false) {}

void Sorter::begin() {
    _servo.setPeriodHertz(50);
    _servo.attach(SORTER_SERVO_PIN, 500, 2400);
    _servo.write(_currentAngle);
    delay(200);
#if ENABLE_DEBUG_PRINTS
    Serial.println("[SORTER] Initialized");
#endif
}

bool Sorter::_moveToAngle(int angle, unsigned long timeout) {
    unsigned long start = millis();
    _busy = true;
    int step = (angle > _currentAngle) ? SORTER_MOVE_STEP_DEG : -SORTER_MOVE_STEP_DEG;
    
    if (step == 0) { 
        _busy = false; 
        return true; 
    }
    
    while (_currentAngle != angle) {
        if (_emergencyFlag) { 
            _busy = false; 
            return false; 
        }
        if (millis() - start > timeout) { 
            _busy = false; 
            return false; 
        }
        
        int next = _currentAngle + step;
        if ((step > 0 && next > angle) || (step < 0 && next < angle)) {
            next = angle;
        }
        
        _servo.write(next);
        _currentAngle = next;
        delay(SORTER_STEP_DELAY_MS);
    }
    
    _busy = false;
    return true;
}

bool Sorter::sortToBin(const String &sizeLabel) {
    int target = SORTER_ANGLE_MEDIUM;
    if (sizeLabel.equalsIgnoreCase("SMALL")) {
        target = SORTER_ANGLE_SMALL;
    } else if (sizeLabel.equalsIgnoreCase("LARGE")) {
        target = SORTER_ANGLE_LARGE;
    }
    
    return _moveToAngle(target, SORTER_MOVE_TIMEOUT_MS);
}

bool Sorter::stow() {
    return _moveToAngle(SORTER_ANGLE_STOW, SORTER_MOVE_TIMEOUT_MS);
}

bool Sorter::isBusy() const {
    return _busy;
}

void Sorter::emergencyStop() {
    _emergencyFlag = true;
    _servo.detach();
    _busy = false;
}
