#include <Servo.h>

const int trigPin = 4;
const int echoPin = 3;

long duration;
int distance;
Servo myServo;
unsigned long previousMillis = 0;  // Tracks time for blinking
const long blinkInterval = 100;    // Interval for LED blink (100 ms)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(50);  // Adjust delay for desired servo speed
    distance = calculateDistance();

    // Blink the LED if distance is less than 10 cm

    // Print the angle and distance for each step
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }

  // Sweep back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(50);
    distance = calculateDistance();

    // Blink the LED if distance is less than 10 cm

    // Print the angle and distance for each step
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}

int calculateDistance() {
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate the distance based on echo pulse duration
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Distance in cm
  return distance;
}
