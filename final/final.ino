#include "HX711.h"
#include <Servo.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 4;

const int SCALE_CALIBRATE_DATA= -530;
const float TARGET_WEIGHT = 150.0;
HX711 scale;

// Servos
const int SERVO_A_PIN = 2;
const int SERVO_B_PIN = 3;
Servo servoA;
Servo servoB;

// Button
const int BUTTON_PIN = 17;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting...");
  
  Serial.println("Initializing the scale...");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(SCALE_CALIBRATE_DATA);
  scale.tare();

  Serial.println("Setting up servos...");
  servoA.attach(SERVO_A_PIN);
  servoB.attach(SERVO_B_PIN);
  servoA.write(0);
  servoB.write(0);
  pinMode(BUTTON_PIN, INPUT);
  Serial.println("Done setup.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Waiting for button...");
  int buttonState = HIGH;
  do {
    buttonState = digitalRead(BUTTON_PIN);
    delay(100);
  } while (buttonState != LOW);

  Serial.println("Button pressed!");
  Serial.println("Releasing the balls!");
  servoB.write(180);
  delay(3000);
  Serial.println("Closing the door!");
  servoB.write(0);
  delay(1000);

  Serial.println("Reseting scale...");
  scale.power_up();
  scale.tare();
  delay(200);
  Serial.println("Opening valve!");
  servoA.write(90);

  Serial.println("Enter measuring loop...");
  float weight = 0;
  do {
    weight = scale.get_units();
    Serial.print("Current weight: ");
    Serial.println(weight, 1);
  } while (weight < TARGET_WEIGHT);

  Serial.println("Target weight reached!");
  Serial.println("Closing the valve!");
  servoA.write(0);
  scale.power_down();
  delay(100);
}
