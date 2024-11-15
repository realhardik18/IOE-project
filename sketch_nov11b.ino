#include <Servo.h>

const int trigPin = 4;
const int echoPin = 3;
const int ledPinClose = 13; // Red LED for distance < 10 cm
const int ledPinFar = 12;   // Blue LED for distance >= 10 cm

long duration;
int distance;
Servo myServo;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPinClose, OUTPUT);
  pinMode(ledPinFar, OUTPUT);
  Serial.begin(9600);
  myServo.attach(9);
}

void loop()
{
  // Sweep from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++)
  {
    myServo.write(angle);       // Move the servo to the current angle
    delay(150);                  // Small delay for servo to reach position
    distance = calculateDistance();

    if (distance < 10)
    {
      digitalWrite(ledPinClose, HIGH); // Turn on the red LED
      digitalWrite(ledPinFar, LOW);    // Turn off the blue LED
      Serial.print("ALERT,");
      Serial.print(angle);
      Serial.print(",");
      Serial.println(distance);
    }
    else
    {
      digitalWrite(ledPinClose, LOW); // Turn off the red LED
      digitalWrite(ledPinFar, HIGH);  // Turn on the blue LED
      Serial.println(angle);         // Print only the angle
    }
  }

  // Sweep back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--)
  {
    myServo.write(angle);
    delay(150);
    distance = calculateDistance();

    if (distance < 10)
    {
      digitalWrite(ledPinClose, HIGH); // Turn on the red LED
      digitalWrite(ledPinFar, LOW);    // Turn off the blue LED
      Serial.print("ALERT,");
      Serial.print(angle);
      Serial.print(",");
      Serial.println(distance);
    }
    else
    {
      digitalWrite(ledPinClose, LOW); // Turn off the red LED
      digitalWrite(ledPinFar, HIGH);  // Turn on the blue LED
      Serial.println(angle);         // Print only the angle
    }
  }
}

int calculateDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; 
  return distance;
}
