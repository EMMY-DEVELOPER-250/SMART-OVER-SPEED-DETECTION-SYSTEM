int button1 = 10;
int button2 = 2;

int led = 6;
int buzzer = 13;

unsigned long time1 = 0;
unsigned long time2 = 0;

float distance = 100.0; // cm between A and B
float speedLimit = 50.0; // cm/s

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Wait for first point
  if (digitalRead(button1) == LOW) {
    time1 = millis();
    Serial.println("Point A triggered");

    // wait until button released
    while(digitalRead(button1) == LOW);

    // wait for second point
    while(digitalRead(button2) != LOW);

    time2 = millis();
    Serial.println("Point B triggered");

    float timeDiff = (time2 - time1) / 1000.0;
    float speed = distance / timeDiff;

    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" cm/s");

    if (speed > speedLimit) {
      // 🚨 Overspeed
      digitalWrite(led, HIGH);
      tone(buzzer, 1000);
      Serial.println("🚨 Overspeed detected!");
    } else {
      // ✅ Safe
      digitalWrite(led, LOW);
      noTone(buzzer);
      Serial.println("Safe speed");
    }

    delay(2000);
  }
}