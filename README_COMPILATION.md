# Compilation Guide - Transformable Pebble Sorting Rover

## Project Structure (Fixed)

```
include/
  ├── configuration.h      # Centralized GPIO and timing configuration
  ├── motors.h            # DC motor control (L298N driver)
  ├── arm.h              # Robotic arm servo control
  ├── gripper.h          # Gripper servo control
  ├── sorter.h           # Pebble sorting servo control
  └── transformation.h   # Rover transformation mechanism servo

src/
  ├── main.cpp           # ESP32 firmware entry point
  ├── motors.cpp         # Motor implementation
  ├── arm.cpp           # Arm implementation
  ├── gripper.cpp       # Gripper implementation
  ├── sorter.cpp        # Sorter implementation
  └── transformation.cpp # Transformation implementation

platformio.ini           # PlatformIO configuration for ESP32
CMakeLists.txt          # CMake build configuration
```

## Prerequisites

- **ESP32 Development Board** (e.g., ESP32-DevKitC)
- **Arduino IDE** (v1.8+) or **Visual Studio Code with PlatformIO**
- **Required Libraries:**
  - ESP32 Servo Library (`arduino-libraries/Servo`)
  - (Optional) Adafruit PWM Servo Driver if using I2C servo multiplexer

## Compilation Methods

### Method 1: PlatformIO (Recommended)

```bash
# Install PlatformIO CLI or use VSCode extension
pio run -e esp32dev              # Build
pio run -e esp32dev -t upload    # Build and upload
pio run -e esp32dev -t monitor   # Monitor serial output
```

### Method 2: Arduino IDE

1. Open Arduino IDE
2. Copy all files from `include/` and `src/` into a single sketch folder
3. Rename headers: `arm.h` → `arm.h` (ensure .h extension)
4. Select **Board**: ESP32 Dev Module
5. Select **COM Port**: (your ESP32 port)
6. Click **Upload**

### Method 3: CMake (Manual Build)

```bash
mkdir build && cd build
cmake ..
make
```

## Hardware Pin Configuration

All pins are defined in `include/configuration.h`. Update these based on your wiring:

```cpp
// Motor Control (L298N Driver)
#define MOTOR_LEFT_PWM_PIN    14  // GPIO14
#define MOTOR_LEFT_DIR_PIN    27  // GPIO27
#define MOTOR_RIGHT_PWM_PIN   12  // GPIO12
#define MOTOR_RIGHT_DIR_PIN   13  // GPIO13

// Servo Pins
#define ARM_SERVO_PIN         21  // GPIO21
#define GRIPPER_SERVO_PIN     22  // GPIO22
#define SORTER_SERVO_PIN      18  // GPIO18
#define TRANSFORM_SERVO_PIN   19  // GPIO19
```

## Serial Protocol

Once compiled and uploaded, communicate with the rover via serial (115200 baud):

```
MOVE,FORWARD,80        # Move forward at speed 80
MOVE,BACKWARD,60       # Move backward
MOVE,LEFT,70           # Turn left
MOVE,RIGHT,70          # Turn right
ARM,HOME               # Arm to home position
ARM,TO_PICKUP          # Arm to pickup position
GRIP,OPEN              # Open gripper
GRIP,CLOSE             # Close gripper
SORT,SMALL             # Sort to small bin
SORT,MEDIUM            # Sort to medium bin
SORT,LARGE             # Sort to large bin
TRANSFORM,FOLD         # Fold rover
TRANSFORM,UNFOLD       # Unfold rover
TRANSFORM,STOW         # Stow to neutral position
STATUS                 # Get current status
EMERGENCY,STOP         # Emergency stop all systems
```

## Common Compilation Issues & Fixes

### Issue: "cannot find -lArduino"
**Solution**: Ensure you're using ESP32 board package. Install via Arduino IDE: Boards Manager → Search "ESP32" → Install

### Issue: "fatal error: ESP32Servo.h: No such file"
**Solution**: Install Servo library in Arduino IDE: Sketch → Include Library → Manage Libraries → Search "Servo" → Install by Michael Margolis

### Issue: GPIO pin conflicts
**Solution**: Check `configuration.h`. ESP32 pins can have multiple functions. Avoid pins used by SPI (5, 18, 19, 23) or UART (1, 3) if not needed.

### Issue: Servo not responding
**Solution**: Verify power supply to servo (5V recommended). Check PWM frequency (50 Hz is standard for servo).

## Testing After Upload

1. Open Serial Monitor (Arduino IDE or PlatformIO Terminal)
2. Set baud rate to **115200**
3. Type commands (e.g., `MOVE,FORWARD,80` + Enter)
4. Expected response: `BUSY` → (action) → `DONE` or `ERROR,<reason>`

## Debugging

Enable debug output in `include/configuration.h`:

```cpp
#define ENABLE_DEBUG_PRINTS 1
#define DEBUG_MOTOR_CONTROL 1
#define DEBUG_SERVO_CONTROL 1
```

This will print detailed logging to serial output.

## Next Steps

- Test each subsystem individually (motors, arm, gripper, sorter, transformation)
- Calibrate servo angles for your specific hardware (see `configuration.h`)
- Integrate Python decision machine (see `src/python/communication.py`)
- Implement vision-based pebble detection (Phase 8-10)
