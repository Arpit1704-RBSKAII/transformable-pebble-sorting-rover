// esp32/transformation.cpp
#include "transformation.h"

Transformation::Transformation() : _currentAngle(TRANSFORM_ANGLE_STOW), _busy(false), _emergencyFlag(false) {}

void Transformation::begin() {
    _servo.setPeriodHertz(50);
    _servo.attach(TRANSFORM_SERVO_PIN, 500, 2400);
    _servo.write(_currentAngle);
    delay(200);
#if ENABLE_DEBUG_PRINTS
    Serial.println("[TRANSFORMATION] Initialized");
#endif
}

bool Transformation::_moveToAngle(int angle, unsigned long timeout) {
    unsigned long start = millis();
    _busy = true;
    int step = (angle > _currentAngle) ? TRANSFORM_MOVE_STEP_DEG : -TRANSFORM_MOVE_STEP_DEG;
    
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
        delay(TRANSFORM_STEP_DELAY_MS);
    }
    
    _busy = false;
    return true;
}

bool Transformation::fold() {
    return _moveToAngle(TRANSFORM_ANGLE_FOLDED, TRANSFORM_MOVE_TIMEOUT_MS);
}

bool Transformation::unfold() {
    return _moveToAngle(TRANSFORM_ANGLE_UNFOLDED, TRANSFORM_MOVE_TIMEOUT_MS);
}

bool Transformation::stow() {
    return _moveToAngle(TRANSFORM_ANGLE_STOW, TRANSFORM_MOVE_TIMEOUT_MS);
}

bool Transformation::isBusy() const {
    return _busy;
}

void Transformation::emergencyStop() {
    _emergencyFlag = true;
    _servo.detach();
    _busy = false;
}
