// esp32/configuration.h
// Integrated configuration for pebble sorting rover

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// --- SERIAL ---
#define SERIAL_BAUD 115200

// --- MOTOR DRIVER PINS (L298N Driver) ---
#define MOTOR_LEFT_PWM_PIN 14    // GPIO14 - PWM for left motor speed
#define MOTOR_LEFT_DIR_PIN 27    // GPIO27 - Direction control for left motor
#define MOTOR_RIGHT_PWM_PIN 12   // GPIO12 - PWM for right motor speed
#define MOTOR_RIGHT_DIR_PIN 13   // GPIO13 - Direction control for right motor
#define MOTOR_MAX_SPEED 255      // PWM duty scale (0..255)
#define MOTOR_ACCEL_STEP 5       // Speed increase/decrease step per cycle
#define MOTOR_ACCEL_DELAY_MS 20  // Delay between acceleration steps

// --- ARM SERVO ---
#define ARM_SERVO_PIN 21
#define ARM_HOME_ANGLE 10
#define ARM_PICKUP_ANGLE 60
#define ARM_BIN_SMALL_ANGLE 100
#define ARM_BIN_MEDIUM_ANGLE 130
#define ARM_BIN_LARGE_ANGLE 160
#define ARM_MOVE_STEP_DEG 3
#define ARM_STEP_DELAY_MS 25
#define ARM_MOVE_TIMEOUT_MS 8000

// --- GRIPPER SERVO ---
#define GRIPPER_SERVO_PIN 22
#define GRIPPER_OPEN_ANGLE 40
#define GRIPPER_CLOSE_ANGLE 90
#define GRIPPER_STEP_DELAY_MS 20
#define GRIPPER_MOVE_TIMEOUT_MS 3000

// --- SORTER (Servo-based bin selector) ---
#define SORTER_SERVO_PIN 18
#define SORTER_ANGLE_STOW 90
#define SORTER_ANGLE_SMALL 30
#define SORTER_ANGLE_MEDIUM 90
#define SORTER_ANGLE_LARGE 150
#define SORTER_MOVE_STEP_DEG 2
#define SORTER_STEP_DELAY_MS 20
#define SORTER_MOVE_TIMEOUT_MS 5000

// --- TRANSFORMATION (Rover shape change) ---
#define TRANSFORM_SERVO_PIN 19
#define TRANSFORM_ANGLE_STOW 90      // Normal state
#define TRANSFORM_ANGLE_FOLDED 20    // Folded/compact state
#define TRANSFORM_ANGLE_UNFOLDED 160 // Extended state
#define TRANSFORM_MOVE_STEP_DEG 3
#define TRANSFORM_STEP_DELAY_MS 25
#define TRANSFORM_MOVE_TIMEOUT_MS 12000

// --- Safety / sensor pins ---
#define PIN_ARM_HOME_SWITCH 34
#define PIN_GRIPPER_CLOSED_SWITCH 35
#define PIN_WHEELS_STOPPED_SIGNAL -1
#define PIN_TRANSFORM_LIMIT_FOLDED -1
#define PIN_TRANSFORM_LIMIT_UNFOLDED -1
#define PIN_EMERGENCY_STOP -1

// --- Logging ---
#define ENABLE_DEBUG_PRINTS 1
#define DEBUG_MOTOR_CONTROL 0
#define DEBUG_SERVO_CONTROL 0

#endif // CONFIGURATION_H
