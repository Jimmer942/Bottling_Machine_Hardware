#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 23, 1, 22, 3);
 
void setup() {
  Serial.begin(115200);
 stepper.setSpeed(10);
}
 
void loop() {
  Serial.println("Vuelta motor");
  stepper.step(STEPS);
  delay(5000);
}
