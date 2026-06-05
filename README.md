# Spooky LED Blinker - Halloween Horror Effect

Arduino-based LED controller that simulates a damaged/malfunctioning fluorescent light with continuous random flickering - perfect for creating a spooky atmosphere for Halloween! Uses a MOSFET for controlling high-power LEDs.

## Features

- **🎃 Continuous Random Flickering**: Never-ending, unpredictable flicker patterns like a damaged fluorescent light
- **👻 Six Horror-Movie Effects**: 
  - Rapid strobing
  - Dim erratic flickering
  - Quick on-off bursts
  - Unstable "trying to stay on" effect
  - Complete failure with recovery attempts
  - Erratic pulsing
- **MOSFET-Based Control**: Supports high-power LEDs using N-Channel MOSFET
- **PWM Brightness Control**: Variable intensity for realistic damaged-light effects
- **Randomized Patterns**: Uses true randomization for unpredictable, spooky behavior

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
   - 220Ω resistor (for MOSFET gate protection) - **REQUIRED**
   - Current-limiting resistor for LED (calculated based on LED specs) - **REQUIRED**
   - 10kΩ resistor (MOSFET gate pull-down) - **OPTIONAL** (recommended for reliability)
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
    | D9  |---[220Ω]---+- G (Gate) -| MOSFET  |
    |     |            |            |         |
    | GND |---------+--+--[10kΩ]- S (Source) -+
    +-----+         |                         |
                    |                         |
                   GND (Common Ground)        |
                                              |
                                             GND


Legend:
  D9   = Arduino Digital Pin 9 (PWM)
  GND  = Ground
  220Ω = Gate protection resistor (REQUIRED)
  10kΩ = Gate pull-down resistor (OPTIONAL - improves reliability)
  R_LED = Current-limiting resistor (REQUIRED - calculated for LED)
  G    = MOSFET Gate
  D    = MOSFET Drain
  S    = MOSFET Source

Note: The 10kΩ pull-down resistor is optional but recommended to ensure
      the MOSFET stays off during Arduino power-up/reset.
```

### Detailed Pin Connections

| Component Pin      | Connects To                          | Required |
|--------------------|--------------------------------------|----------|
| Arduino Pin 9      | 220Ω resistor → MOSFET Gate         | Yes      |
| Arduino GND        | Power Supply GND & MOSFET Source    | Yes      |
| MOSFET Gate        | 220Ω resistor → Arduino Pin 9       | Yes      |
| MOSFET Gate        | 10kΩ resistor → MOSFET Source       | Optional |
| MOSFET Drain       | LED Cathode (-)                     | Yes      |
| MOSFET Source      | GND (Common Ground)                 | Yes      |
| LED Anode (+)      | Current-limiting resistor → V+      | Yes      |
| LED Cathode (-)    | MOSFET Drain                        | Yes      |
| Power Supply (+)   | Current-limiting resistor → LED +   | Yes      |
| Power Supply GND   | Arduino GND & MOSFET Source         | Yes      |

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

Once uploaded, the LED will continuously flicker with random horror-movie effects:
1. **Rapid Strobing**: Quick on-off flashes (3-8 strobes)
2. **Dim Flickering**: Random low-brightness flickers
3. **Quick Bursts**: Brief flashes with longer dark periods
4. **Unstable On**: Trying to stay on but randomly dipping in brightness
5. **Failure Recovery**: Complete darkness followed by failed recovery attempts
6. **Erratic Pulsing**: Random fade-ups and quick drops

The patterns are randomly selected and never repeat in the same sequence - **the flickering never stops!**

### 4. Serial Monitor (Optional)

Open the Serial Monitor (`Ctrl+Shift+M`) at 9600 baud to see:
```
Spooky LED - Damaged Fluorescent Simulation
Halloween Horror Effect - Continuous Random Flickering
Starting...
```

## Configuration

You can customize the spooky effect by modifying these parameters in the code:

```cpp
const int FLICKER_MIN_TIME = 10;      // Minimum flicker duration in ms (default: 10)
const int FLICKER_MAX_TIME = 300;     // Maximum flicker duration in ms (default: 300)
const int STABLE_MIN_TIME = 500;      // Min time for "unstable on" effect (default: 500)
const int STABLE_MAX_TIME = 3000;     // Max time for "unstable on" effect (default: 3000)
const int DIM_MIN_BRIGHTNESS = 50;    // Minimum brightness during dim flickers (default: 50)
const int DIM_MAX_BRIGHTNESS = 180;   // Maximum brightness during dim flickers (default: 180)
```

**For more intense horror effect**: Decrease `FLICKER_MIN_TIME` and increase pattern frequency
**For subtler creepy effect**: Increase delay values and reduce brightness range

## How It Works

### Damaged Fluorescent Light Simulation

The code continuously cycles through six different flicker patterns randomly:

1. **Rapid Strobing**: Classic horror movie effect with 3-8 quick flashes
2. **Dim Flickering**: Low-intensity random brightness variations (50-180 PWM)
3. **Quick Bursts**: Brief flashes separated by longer dark periods
4. **Unstable On**: Light tries to stay on but randomly dips in brightness (40% chance per cycle)
5. **Failure Recovery**: Complete darkness (300-1000ms) followed by failed recovery attempts
6. **Erratic Pulsing**: Random fade-up sequences with quick drops

Each pattern is randomly selected in `loop()` with a 50-500ms delay between patterns for maximum unpredictability.

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