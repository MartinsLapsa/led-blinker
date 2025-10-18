/*
 * LED Blinker with Fluorescent Light Simulation
 * 
 * This Arduino sketch simulates the flickering behavior of fluorescent lights
 * when they start up. The LED is controlled via a MOSFET for high-power applications.
 * 
 * Circuit:
 * - Arduino PWM pin (Pin 9) -> MOSFET Gate (through 220Ω resistor)
 * - MOSFET Drain -> LED Cathode (-)
 * - LED Anode (+) -> Power Supply (+) (through appropriate current-limiting resistor)
 * - MOSFET Source -> Ground
 * - Power Supply Ground -> Arduino Ground
 * 
 * Components:
 * - Arduino (Uno/Nano/Mega)
 * - N-Channel MOSFET (e.g., IRF520, IRF540, or IRLZ44N for logic-level)
 * - LED (any color, any power rating)
 * - 220Ω resistor (gate resistor)
 * - Current-limiting resistor for LED (calculated based on LED specs)
 * - Power supply (5V-12V depending on LED requirements)
 */

// Pin definitions
const int MOSFET_PIN = 9;  // PWM-capable pin connected to MOSFET gate

// Fluorescent simulation parameters
const int STARTUP_FLICKERS = 5;     // Number of initial flickers
const int FLICKER_MIN_TIME = 50;    // Minimum flicker duration (ms)
const int FLICKER_MAX_TIME = 150;   // Maximum flicker duration (ms)
const int WARMUP_FLICKERS = 3;      // Number of warmup flickers before stable
const int STABLE_DURATION = 5000;   // How long to stay on before cycling (ms)
const int OFF_DURATION = 3000;      // How long to stay off between cycles (ms)

void setup() {
  // Initialize the MOSFET control pin
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);
  
  // Optional: Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("LED Blinker - Fluorescent Simulation");
  Serial.println("Starting...");
}

void loop() {
  // Simulate fluorescent light startup sequence
  fluorescentStartup();
  
  // Keep light on for stable duration
  digitalWrite(MOSFET_PIN, HIGH);
  Serial.println("LED: Stable ON");
  delay(STABLE_DURATION);
  
  // Turn off
  digitalWrite(MOSFET_PIN, LOW);
  Serial.println("LED: OFF");
  delay(OFF_DURATION);
}

/*
 * Simulates the characteristic flickering of a fluorescent light during startup
 */
void fluorescentStartup() {
  Serial.println("Starting fluorescent simulation...");
  
  // Phase 1: Initial rapid flickers (trying to ignite)
  for (int i = 0; i < STARTUP_FLICKERS; i++) {
    int flickerTime = random(FLICKER_MIN_TIME, FLICKER_MAX_TIME);
    
    // Quick on-off flicker
    digitalWrite(MOSFET_PIN, HIGH);
    delay(flickerTime);
    digitalWrite(MOSFET_PIN, LOW);
    delay(flickerTime / 2);
    
    Serial.print("Flicker ");
    Serial.println(i + 1);
  }
  
  // Phase 2: Warmup flickers (partial brightness, gradually stabilizing)
  for (int i = 0; i < WARMUP_FLICKERS; i++) {
    // Use PWM to simulate partial brightness during warmup
    int brightness = map(i, 0, WARMUP_FLICKERS - 1, 100, 255);
    
    analogWrite(MOSFET_PIN, brightness);
    delay(200);
    analogWrite(MOSFET_PIN, 0);
    delay(100 - (i * 30)); // Delays get shorter as it stabilizes
    
    Serial.print("Warmup ");
    Serial.println(i + 1);
  }
  
  // Phase 3: Final flicker before becoming stable
  for (int i = 0; i < 2; i++) {
    analogWrite(MOSFET_PIN, 200);
    delay(80);
    analogWrite(MOSFET_PIN, 255);
    delay(50);
  }
  
  Serial.println("Fluorescent startup complete!");
}
