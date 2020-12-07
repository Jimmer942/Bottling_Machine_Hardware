#include <Stepper.h> // Includes the librarie to control the stepper motor
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"


#define STEPS 1 // This is the number of steps per second that the motor do
Stepper stepper(STEPS, 23, 1, 22, 3); // This instance the stepper library and initialize the motor giving the steps and the pins on the hardware

int relay = 39; // Sets the control pin for the relay in 39
const int sensorObj = 36; // Sets the sensing pin to 36
bool flag = LOW;


TaskHandle_t Motor_Handle;
TaskHandle_t Object_Handle;
TaskHandle_t Relay_Handle;

void setup()
{
  Serial.begin(115200);

  stepper.setSpeed(10); // This function sets the motor's speed in RPM
  pinMode(relay, OUTPUT); //Sets the GPIO pin 39 to OUTPUT
  pinMode(sensorObj, INPUT);  //Sets the GPIO pin 39 to INPUT

  xTaskCreate(
    SenseObject, /* Task function. */
    "Sense an Object", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    5, /* priority of the task */
    &Object_Handle); /* Task handle to keep track of created task */

  /* we create a new task here */
  xTaskCreate(
    MoveMotor, /* Task function. */
    "Move the motor", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    2, /* priority of the task */
    &Motor_Handle); /* Task handle to keep track of created task */



  /* we create a new task here */
  xTaskCreate(
    ActRelay, /* Task function. */
    "another Task", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    2, /* priority of the task */
    &Relay_Handle); /* Task handle to keep track of created task */
}

/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
}
void SenseObject(void *param) {
  for (;;) {
    vTaskSuspend(Relay_Handle);
    Serial.println("Sensing an object");
    bool value = digitalRead(sensorObj);  //lectura digital de pin
    if (value == LOW && flag == LOW) {
      Serial.println("Detectado obstaculo");
      vTaskSuspend(Motor_Handle);
      vTaskResume(Relay_Handle);
      vTaskSuspend(NULL);
    }
    flag = !value;
    delay(100);
  }
}

// This function will be invoked a task thta will make the motor run
void MoveMotor(void *param) {
  // this is the action that the task will execute when it is called
  for (;;) {
    /*TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed = 1;
    TIMERG0.wdt_wprotect = 0;*/
    Serial.println("Motor is running");
    delay(100);
    //vTaskDelay(100);
      stepper.step(STEPS); // Here the start the motor to runs a number of steps
      //vTaskDelay(100);
  }
}


void ActRelay(void *params) {
  for (;;) {
    // digitalWrite(relay, HIGH); // envia señal alta al relay
    Serial.println("Relay accionado");
    delay(5000);           // 1 segundo

    digitalWrite(relay, LOW);  // envia señal baja al relay
    Serial.println("Relay no accionado");
    delay(10);// 1 segundo
    vTaskResume(Motor_Handle);
    delay(10);// 1 segundo
    vTaskResume(Object_Handle);
    vTaskSuspend(NULL);
  }
}
