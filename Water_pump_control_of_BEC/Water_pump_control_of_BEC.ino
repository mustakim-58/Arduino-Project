// Collected from gemini

const int switches[] = {2, 3, 4, 5, 6}; // Pins for the switches
const int ledPin = 9; // Pin for the LED

int lightState = 0; 

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(switches[i], INPUT_PULLUP);
  }
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(switches[i]) == LOW) {
      lightState = !lightState;
      break; // Exit the loop if any switch is pressed
    }
  }

  digitalWrite(ledPin, lightState);
}