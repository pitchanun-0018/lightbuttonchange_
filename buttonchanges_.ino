// Define component pins according to the assignment
const int buttonPin = 2; // Push button connected to D2
const int ledPin = 3;    // LED light connected to D3

// Variable to store the current lighting mode (0=Steady, 1=Slow, 2=Medium, 3=Fast)
int mode = 0;

// Variables for button state detection
int buttonState = 0;
int lastButtonState = 0;

// Variables for non-blocking blink timing using millis()
unsigned long previousMillis = 0;
int ledState = LOW; // For Common Anode RGB LED module: LOW = ON, HIGH = OFF

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Initial state: Steady lighting when powered on
  digitalWrite(ledPin, LOW);
}

void loop() {
  // 1. Read the push button state
  buttonState = digitalRead(buttonPin);

  // Detect a new button press (state change from unpressed to pressed)
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) { // Change HIGH to LOW if your button module is Active-Low
      mode++;                  // Advance to the next mode
      if (mode > 3) {
        mode = 0;              // 4th press resets back to Mode 0 (Steady lighting)
      }
    }
    delay(50); // Short debounce delay to prevent false triggers
  }
  lastButtonState = buttonState;

  // 2. Control LED behavior based on the current mode
  unsigned long currentMillis = millis();

  if (mode == 0) {
    // Initial state / 4th press: Steady lighting
    digitalWrite(ledPin, LOW);
  } 
  else if (mode == 1) {
    // 1st press: Slow blink (every 1000ms / 1 second)
    blinkLED(currentMillis, 1000);
  } 
  else if (mode == 2) {
    // 2nd press: Medium blink (every 500ms / 0.5 seconds)
    blinkLED(currentMillis, 500);
  } 
  else if (mode == 3) {
    // 3rd press: Fast blink (every 150ms / 0.15 seconds)
    blinkLED(currentMillis, 150);
  }
}

// Helper function to toggle the LED at a specific interval
void blinkLED(unsigned long currentMillis, long interval) {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Toggle LED state
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}