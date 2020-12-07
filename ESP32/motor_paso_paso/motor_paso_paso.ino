#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 8, 10, 9, 11 );
 
void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
}
 
void loop() {
  Serial.println("Vuelta motor");
  stepper.step(STEPS);
  delay(5000);
}
