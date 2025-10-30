/*
 * Simple LED Blinker - Arduino Nano Built-in LED
 *
 * Blinks the built-in LED on Arduino Nano (Pin 13).
 * No external components required - perfect for testing the board.
 */

const int LED_PIN = 9;  // Built-in LED on Pin 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Simple LED Blinker - Arduino Nano Built-in LED");
}

void loop() {
  // Turn LED ON
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED: ON");
  delay(1000);  // Wait 1 second

  // Turn LED OFF
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED: OFF");
  delay(1000);  // Wait 1 second
}
