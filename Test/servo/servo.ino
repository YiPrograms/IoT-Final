#include <Servo.h>
Servo servoA;
Servo servoB;

int buttonState = 0;


void setup() {
  servoA.attach(2);
  servoB.attach(3);
  pinMode(0, INPUT);
}

void loop() { 
    servoA.write(0);
    servoB.write(0);
    delay(1000);
    servoA.write(90);
    servoB.write(90);
    delay(1000);
    servoA.write(180);
    servoB.write(180);
    delay(1000);
    servoA.write(90);
    servoB.write(90);
    delay(1000);

}
