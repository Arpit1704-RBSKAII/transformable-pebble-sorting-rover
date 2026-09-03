// esp32/arm.cpp
#include "arm.h"

Arm::Arm() : _currentAngle(ARM_HOME_ANGLE), _busy(false), _emergencyFlag(false) {}

void Arm::begin() {
    _servo.setPeriodHertz(50);
    _servo.attach(ARM_SERVO_PIN, 500, 2400);
    _servo.write(_currentAngle);
    delay(200);
#if ENABLE_DEBUG_PRINTS
    Serial.println("[ARM] Initialized");
#endif
}

bool Arm::_moveToAngle(int angle, String &errOut) {
    unsigned long start = millis();
    _busy = true;
    int step = (angle > _currentAngle) ? ARM_MOVE_STEP_DEG : -ARM_MOVE_STEP_DEG;
    
    if (step == 0) { 
        _busy = false; 
        return true; 
    }
    
    while (_currentAngle != angle) {
        if (_emergencyFlag) { 
            errOut = "EMERGENCY_ABORT"; 
            _busy = false; 
            return false; 
        }
        if (millis() - start > ARM_MOVE_TIMEOUT_MS) { 
            errOut = "TIMEOUT"; 
            _busy = false; 
            return false; 
        }
        
        int next = _currentAngle + step;
        if ((step > 0 && next > angle) || (step < 0 && next < angle)) {
            next = angle;
        }
        
        _servo.write(next);
        _currentAngle = next;
        delay(ARM_STEP_DELAY_MS);
    }
    
    _busy = false;
    return true;
}

bool Arm::moveHome() {
    String err;
    return _moveToAngle(ARM_HOME_ANGLE, err);
}

bool Arm::moveToPickup() {
    String err;
    return _moveToAngle(ARM_PICKUP_ANGLE, err);
}

bool Arm::moveToBin(const String &sizeLabel) {
    int target = ARM_BIN_MEDIUM_ANGLE;
    if (sizeLabel.equalsIgnoreCase("SMALL")) {
        target = ARM_BIN_SMALL_ANGLE;
    } else if (sizeLabel.equalsIgnoreCase("LARGE")) {
        target = ARM_BIN_LARGE_ANGLE;
    }
    String err;
    return _moveToAngle(target, err);
}

bool Arm::isExtended() const {
    return _currentAngle != ARM_HOME_ANGLE;
}

void Arm::emergencyStop() {
    _emergencyFlag = true;
    _servo.detach();
    _busy = false;
}
