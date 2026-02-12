#define TRIG_PIN 10
#define ECHO_PIN 11
#include <Servo.h>

int sensorState = 0;
float threshold = 10;
Servo myservo;  // create Servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN,HIGH);
  float distance = duration * 0.034 / 2;
  return distance;


}

void loop() {
  float distance = readDistance();

  if(distance > 0 && distance <= threshold){
    sensorState = 1;
    myservo.write(90);                  // sets the servo position according to the scaled value
    delay(1500);
  }
  
  sensorState=0;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Sensor state: ");
  Serial.println(sensorState);

  myservo.write(180);
  delay(100);
}
