# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an Arduino-based LED controller that simulates a malfunctioning fluorescent light with continuous random flickering - specifically designed for Halloween horror effects. The project uses MOSFET-based control to support high-power LEDs with PWM brightness control.

## Project Structure

- **led_blinker.ino** - Main Arduino sketch with spooky Halloween effect (6 random flicker patterns)
- **simple_blink.ino** - Basic test sketch for verifying hardware setup (simple on/off blink)
- **README.md** - Complete documentation with wiring diagrams, component specs, and troubleshooting
- **PROJECT_SUMMARY.txt** - Quick overview of all files and project status
- **CIRCUIT_DIAGRAM.txt** - Detailed circuit schematic with component specifications
- **WIRING_GUIDE.txt** - Step-by-step visual wiring instructions

## Hardware Architecture

**Circuit Design**: Low-side N-channel MOSFET switching configuration
- Arduino Pin 9 (PWM) controls MOSFET gate through 220Ω protection resistor
- MOSFET drain connected to LED cathode
- MOSFET source connected to common ground
- LED anode connected to power supply through current-limiting resistor
- **Critical**: All grounds must be connected together (Arduino GND, PSU GND, MOSFET source)

**Key Components**:
- IRLZ44N N-Channel MOSFET (logic-level, recommended for Arduino 5V operation)
- 220Ω gate protection resistor (REQUIRED)
- 10kΩ pull-down resistor (OPTIONAL but recommended)
- Current-limiting resistor (calculated per LED specifications)

## Code Architecture

### Main Sketch (led_blinker.ino)

**Core Design Pattern**: Random pattern selection with continuous loop
- `loop()` randomly selects from 6 flicker patterns (case 0-5)
- Each pattern function implements specific horror effect
- No fixed sequence - patterns never repeat predictably

**Six Flicker Patterns**:
1. `rapidStrobe()` - Classic horror movie rapid on/off flashes
2. `dimFlicker()` - Variable PWM brightness (50-180 range)
3. `quickBursts()` - Brief flashes with longer dark periods
4. `unstableOn()` - Attempts to stay on with random brightness dips
5. `failureRecovery()` - Complete darkness followed by failed recovery attempts
6. `erraticPulse()` - Random fade-up sequences with quick drops

**PWM Usage**: Pin 9 used for both digital (HIGH/LOW) and analog (0-255) control
- Full brightness: `digitalWrite(MOSFET_PIN, HIGH)` or `analogWrite(MOSFET_PIN, 255)`
- Variable: `analogWrite(MOSFET_PIN, value)` where value = 0-255
- Off: `digitalWrite(MOSFET_PIN, LOW)` or `analogWrite(MOSFET_PIN, 0)`

**Timing Parameters** (configurable constants):
- `FLICKER_MIN_TIME` / `FLICKER_MAX_TIME` - Individual flicker duration range
- `STABLE_MIN_TIME` / `STABLE_MAX_TIME` - Duration for "unstable on" effect
- `DIM_MIN_BRIGHTNESS` / `DIM_MAX_BRIGHTNESS` - PWM range for dim flickers

### Test Sketch (simple_blink.ino)

Simple 1-second on/off blink for hardware validation. Always test with this first before uploading main sketch.

## Development Workflow

### Testing Hardware
1. Start with `simple_blink.ino` to verify circuit wiring
2. Open Serial Monitor at 9600 baud to confirm operation
3. Once hardware verified, upload `led_blinker.ino`

### Arduino IDE Usage
- Board: Arduino Uno (or compatible)
- Port: Select appropriate COM port (Windows) or /dev/ttyUSB* (Linux/Mac)
- Upload: Ctrl+U or Upload button
- Serial Monitor: Ctrl+Shift+M (9600 baud)

### Modifying Flicker Effects

To add new pattern:
1. Create new function following existing pattern (e.g., `void newPattern() {}`)
2. Increment range in `random(0, 6)` to `random(0, 7)` in `loop()`
3. Add new case to switch statement
4. Use `digitalWrite()` for on/off, `analogWrite()` for PWM brightness

To adjust intensity:
- Modify `DIM_MIN_BRIGHTNESS` / `DIM_MAX_BRIGHTNESS` constants
- Adjust delay ranges in pattern functions
- Change probability in `unstableOn()` (currently 40% chance of dip)

### Component Substitutions

**MOSFET Requirements**:
- Must be N-channel enhancement mode
- Logic-level (Vgs_th < 2V) for Arduino 5V compatibility
- Recommended: IRLZ44N, IRL540N
- Non-logic-level alternatives (IRF520, IRF540) require MOSFET driver

**LED Compatibility**:
- Standard 5mm LEDs: Use calculated current-limiting resistor
- High-power LEDs (1W+): Use constant current driver instead of resistor
- LED strips: Ensure total current within MOSFET rating

## Safety Considerations

- **Common Ground Rule**: Arduino GND, power supply GND, and MOSFET source MUST be connected together
- **Polarity**: LEDs are polarized (anode = +, cathode = -)
- **Heat Management**: High-power applications require heatsinks on both LED and MOSFET
- **Current Rating**: Verify MOSFET can handle LED current (check datasheet)
- **Resistor Wattage**: Calculate power dissipation: P = I² × R

## Troubleshooting

- **LED dim/doesn't light**: Use logic-level MOSFET (IRLZ44N), not standard MOSFET
- **LED always on/off**: Check Pin 9 connection and wiring
- **MOSFET overheating**: Add heatsink or reduce LED current
- **No flicker effect**: Verify code uploaded, check Serial Monitor output
- **Erratic behavior**: Check all grounds are connected together
