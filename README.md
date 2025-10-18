# LED Blinker with Fluorescent Light Simulation

Arduino-based LED controller that simulates the characteristic flickering behavior of fluorescent lights during startup. Uses a MOSFET for controlling high-power LEDs.

## Features

- **Fluorescent Light Simulation**: Mimics the startup sequence of fluorescent lights with realistic flickering
- **MOSFET-Based Control**: Supports high-power LEDs using N-Channel MOSFET
- **PWM Brightness Control**: Gradual brightness ramping during warmup phase
- **Configurable Parameters**: Easy adjustment of flicker patterns and timing

## Hardware Requirements

### Components List

1. **Arduino Board** (Uno, Nano, or Mega recommended)
2. **N-Channel MOSFET** (choose one):
   - IRF520 (Standard, requires 10V gate voltage)
   - IRF540 (Higher current capacity)
   - IRLZ44N (Logic-level, works with 5V - **RECOMMENDED for Arduino**)
   - IRL540N (Logic-level alternative)
3. **LED** (any type):
   - Standard 5mm LED (20mA)
   - High-power LED (1W, 3W, etc.)
   - LED strip
4. **Resistors**:
   - 220Ω resistor (for MOSFET gate protection)
   - Current-limiting resistor for LED (calculated based on LED specs)
5. **Power Supply**:
   - 5V-12V DC (depending on LED voltage requirements)
   - Sufficient current rating for your LED
6. **Breadboard and jumper wires** (for prototyping)

### Current-Limiting Resistor Calculation

For standard LEDs:
```
R = (V_supply - V_led) / I_led

Example for 5mm red LED (2.0V, 20mA) with 12V supply:
R = (12V - 2.0V) / 0.02A = 500Ω (use 470Ω or 560Ω standard value)
```

For high-power LEDs, use a constant current driver instead of a resistor.

## Wiring Diagram

```
                                    +12V Power Supply
                                         |
                                         |
                                       [R_LED]  (Current-limiting resistor)
                                         |
                                         |
                                      [LED +]  (Anode)
                                         |
                                      [LED -]  (Cathode)
                                         |
                                         |
    Arduino                              D (Drain)
    +-----+                         +----+----+
    |     |                         |         |
    | D9  |---[220Ω]--- G (Gate) ---| MOSFET  |
    |     |                         |         |
    | GND |---------------------- S (Source) -+
    +-----+                                   |
                                              |
                                             GND (Common Ground)


Legend:
  D9  = Arduino Digital Pin 9 (PWM)
  GND = Ground
  R   = Resistor
  G   = MOSFET Gate
  D   = MOSFET Drain
  S   = MOSFET Source
```

### Detailed Pin Connections

| Component Pin      | Connects To                          |
|--------------------|--------------------------------------|
| Arduino Pin 9      | 220Ω resistor → MOSFET Gate         |
| Arduino GND        | Power Supply GND & MOSFET Source    |
| MOSFET Gate        | 220Ω resistor → Arduino Pin 9       |
| MOSFET Drain       | LED Cathode (-)                     |
| MOSFET Source      | GND (Common Ground)                 |
| LED Anode (+)      | Current-limiting resistor → V+      |
| LED Cathode (-)    | MOSFET Drain                        |
| Power Supply (+)   | Current-limiting resistor → LED +   |
| Power Supply GND   | Arduino GND & MOSFET Source         |

## Installation & Usage

### 1. Hardware Setup

1. Connect components according to the wiring diagram above
2. Ensure the MOSFET is a logic-level type (IRLZ44N recommended) or use a MOSFET driver
3. Double-check all connections before applying power
4. **Important**: Connect all grounds together (Arduino GND, Power Supply GND, MOSFET Source)

### 2. Software Upload

1. Open `led_blinker.ino` in Arduino IDE
2. Select your Arduino board: **Tools > Board > Arduino Uno** (or your board model)
3. Select the correct port: **Tools > Port > COM_X** (Windows) or **/dev/ttyUSB_X** (Linux/Mac)
4. Click **Upload** button or press `Ctrl+U`
5. Wait for upload to complete

### 3. Operation

Once uploaded, the LED will:
1. **Start flickering** rapidly (simulating fluorescent ignition)
2. **Warm up** with gradually increasing brightness
3. **Stabilize** to full brightness
4. **Stay on** for 5 seconds
5. **Turn off** for 3 seconds
6. **Repeat** the cycle

### 4. Serial Monitor (Optional)

Open the Serial Monitor (`Ctrl+Shift+M`) at 9600 baud to see status messages:
- Flicker counts
- Warmup progress
- Stable state indicators

## Configuration

You can customize the behavior by modifying these parameters in the code:

```cpp
const int STARTUP_FLICKERS = 5;     // Number of initial flickers (default: 5)
const int FLICKER_MIN_TIME = 50;    // Minimum flicker duration in ms (default: 50)
const int FLICKER_MAX_TIME = 150;   // Maximum flicker duration in ms (default: 150)
const int WARMUP_FLICKERS = 3;      // Number of warmup flickers (default: 3)
const int STABLE_DURATION = 5000;   // On time in ms (default: 5000)
const int OFF_DURATION = 3000;      // Off time in ms (default: 3000)
```

## How It Works

### Fluorescent Light Simulation

The code simulates three phases of fluorescent light startup:

1. **Phase 1 - Initial Flickers**: Rapid on/off cycles simulating the tube trying to ignite
2. **Phase 2 - Warmup**: Progressive brightness increase using PWM with decreasing flicker intervals
3. **Phase 3 - Stabilization**: Final quick flickers before reaching stable full brightness

### MOSFET Control

- **PWM (Pin 9)**: Provides variable voltage (0-5V) to MOSFET gate
- **Gate Resistor**: Protects Arduino pin from current spikes
- **Low-side switching**: LED positive connected to power supply, negative controlled by MOSFET
- **Logic-level MOSFET**: Fully turns on with 5V gate voltage from Arduino

## Safety Notes

⚠️ **Important Safety Information**

1. **Power Supply**: Ensure voltage matches your LED specifications
2. **Current Rating**: MOSFET must handle the LED current (check datasheet)
3. **Heat Dissipation**: High-power LEDs and MOSFETs may require heatsinks
4. **Polarity**: LEDs are polarized - connect anode to (+), cathode to (-)
5. **Common Ground**: All grounds MUST be connected together
6. **Resistor Wattage**: Use appropriate wattage rating for current-limiting resistor
   - Power (W) = I² × R
   - Example: 20mA through 500Ω = (0.02)² × 500 = 0.2W (use 0.25W or 0.5W resistor)

## Troubleshooting

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LED doesn't light up | Wrong MOSFET type | Use logic-level MOSFET (IRLZ44N) |
| LED always on/off | Wrong pin or connection | Verify Pin 9 connection and wiring |
| Dim LED | Insufficient gate voltage | Use logic-level MOSFET or add MOSFET driver |
| MOSFET gets hot | Too much current | Check LED current, add heatsink |
| No flicker effect | Code not uploaded | Re-upload sketch, check Serial Monitor |
| Erratic behavior | Ground issue | Ensure all grounds connected together |

## Schematic Diagram

For a more detailed schematic, see `CIRCUIT_DIAGRAM.txt` which includes component values and technical specifications.

## License

This project is open source and available for educational and personal use.

## Contributing

Feel free to submit issues or pull requests for improvements or additional features.

## Credits

Created for Arduino-based LED control projects with realistic fluorescent light simulation.