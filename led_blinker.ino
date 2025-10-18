/*
 * Spooky LED Blinker - Damaged Fluorescent Light Simulation
 * 
 * This Arduino sketch simulates a damaged/malfunctioning fluorescent light
 * with random, continuous flickering - perfect for Halloween horror effects!
 * The LED is controlled via a MOSFET for high-power applications.
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

// Spooky flicker parameters for damaged fluorescent effect
const int FLICKER_MIN_TIME = 10;      // Minimum flicker duration (ms)
const int FLICKER_MAX_TIME = 300;     // Maximum flicker duration (ms)
const int STABLE_MIN_TIME = 500;      // Minimum time to stay somewhat stable (ms)
const int STABLE_MAX_TIME = 3000;     // Maximum time to stay somewhat stable (ms)
const int DIM_MIN_BRIGHTNESS = 50;    // Minimum brightness during dim flickers
const int DIM_MAX_BRIGHTNESS = 180;   // Maximum brightness during dim flickers

void setup() {
  // Initialize the MOSFET control pin
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);
  
  // Seed random number generator for unpredictable flickering
  randomSeed(analogRead(0));
  
  // Optional: Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Spooky LED - Damaged Fluorescent Simulation");
  Serial.println("Halloween Horror Effect - Continuous Random Flickering");
  Serial.println("Starting...");
}

void loop() {
  // Randomly choose a flicker pattern for spooky, unpredictable behavior
  int pattern = random(0, 6);
  
  switch(pattern) {
    case 0:
      // Rapid strobing - horror movie classic
      rapidStrobe();
      break;
      
    case 1:
      // Dim flickering with random brightness
      dimFlicker();
      break;
      
    case 2:
      // Quick on-off bursts
      quickBursts();
      break;
      
    case 3:
      // Unstable "almost on" flickering
      unstableOn();
      break;
      
    case 4:
      // Complete failure then recovery
      failureRecovery();
      break;
      
    case 5:
      // Erratic pulsing
      erraticPulse();
      break;
  }
  
  // Random delay between patterns for unpredictability
  delay(random(50, 500));
}

/*
 * Rapid strobing effect - classic horror movie flicker
 */
void rapidStrobe() {
  int strobes = random(3, 8);
  for (int i = 0; i < strobes; i++) {
    digitalWrite(MOSFET_PIN, HIGH);
    delay(random(20, 80));
    digitalWrite(MOSFET_PIN, LOW);
    delay(random(20, 100));
  }
}

/*
 * Dim flickering with varying brightness
 */
void dimFlicker() {
  int flickers = random(2, 5);
  for (int i = 0; i < flickers; i++) {
    int brightness = random(DIM_MIN_BRIGHTNESS, DIM_MAX_BRIGHTNESS);
    analogWrite(MOSFET_PIN, brightness);
    delay(random(50, 200));
    analogWrite(MOSFET_PIN, 0);
    delay(random(30, 150));
  }
}

/*
 * Quick burst sequences
 */
void quickBursts() {
  int bursts = random(2, 4);
  for (int i = 0; i < bursts; i++) {
    // Quick on
    digitalWrite(MOSFET_PIN, HIGH);
    delay(random(FLICKER_MIN_TIME, 50));
    digitalWrite(MOSFET_PIN, LOW);
    delay(random(100, 300));
  }
}

/*
 * Unstable "trying to stay on" effect
 */
void unstableOn() {
  int duration = random(STABLE_MIN_TIME, STABLE_MAX_TIME);
  long startTime = millis();
  
  while (millis() - startTime < duration) {
    // Mostly on with random dips
    analogWrite(MOSFET_PIN, 255);
    delay(random(100, 500));
    
    // Random dip in brightness
    if (random(0, 100) < 40) {  // 40% chance of dip
      analogWrite(MOSFET_PIN, random(0, 150));
      delay(random(20, 100));
    }
  }
  
  // Sudden failure
  digitalWrite(MOSFET_PIN, LOW);
  delay(random(200, 800));
}

/*
 * Complete failure then random recovery attempts
 */
void failureRecovery() {
  // Complete darkness
  digitalWrite(MOSFET_PIN, LOW);
  delay(random(300, 1000));
  
  // Failed recovery attempts
  int attempts = random(3, 6);
  for (int i = 0; i < attempts; i++) {
    // Brief flash
    analogWrite(MOSFET_PIN, random(100, 255));
    delay(random(10, 50));
    digitalWrite(MOSFET_PIN, LOW);
    delay(random(100, 400));
  }
}

/*
 * Erratic pulsing with random intensity
 */
void erraticPulse() {
  int pulses = random(3, 7);
  for (int i = 0; i < pulses; i++) {
    // Fade up
    int targetBrightness = random(100, 255);
    for (int b = 0; b <= targetBrightness; b += random(5, 30)) {
      analogWrite(MOSFET_PIN, b);
      delay(random(5, 20));
    }
    
    // Hold briefly
    delay(random(20, 100));
    
    // Quick drop
    digitalWrite(MOSFET_PIN, LOW);
    delay(random(50, 200));
  }
}
