/*
 * Simple LED Blinker - Basic Example
 * 
 * This is a simplified version for testing the MOSFET circuit.
 * Use this sketch to verify your hardware setup before trying
 * the full fluorescent simulation.
 * 
 * Circuit: Same as led_blinker.ino
 * - Arduino Pin 9 → 220Ω resistor → MOSFET Gate
 * - MOSFET Drain → LED Cathode (-)
 * - MOSFET Source → Ground
 * - LED Anode (+) → Current-limiting resistor → Power Supply (+)
 * - All grounds connected together
 */

const int MOSFET_PIN = 9;  // PWM-capable pin

void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Simple LED Blinker - Testing Circuit");
}

void loop() {
  // Turn LED ON
  digitalWrite(MOSFET_PIN, HIGH);
  Serial.println("LED: ON");
  delay(1000);  // Wait 1 second
  
  // Turn LED OFF
  digitalWrite(MOSFET_PIN, LOW);
  Serial.println("LED: OFF");
  delay(1000);  // Wait 1 second
}
