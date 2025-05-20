// 👏 Clap Switch using Arduino Uno

#define SENSOR_PIN 2      // Pin connected to sound sensor
#define RELAY_PIN 3       // Pin connected to relay module

int previousValue = HIGH; // Store last sensor reading
int clapCount = 0;        // Counter for claps
unsigned long previousTime = millis(); // Time of first clap
bool relayOutput = HIGH;  // Relay output state (HIGH = OFF for LOW-level relay)

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Turn OFF relay initially (for LOW-level triggered relays)
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  int currentValue = digitalRead(SENSOR_PIN);

  // Detect falling edge (clap)
  if (previousValue == HIGH && currentValue == LOW) {
    // Reset clap count if too much time has passed
    if (clapCount == 1 && millis() - previousTime >= 500) {
      clapCount = 0;
    }

    // Record time of first clap
    if (clapCount == 0) {
      previousTime = millis();
    }

    clapCount++;

    // Toggle relay after two claps
    if (clapCount == 2) {
      relayOutput = !relayOutput;
      digitalWrite(RELAY_PIN, relayOutput);
      clapCount = 0;
    }

    delay(200); // Debounce delay
  }

  previousValue = currentValue;
}
