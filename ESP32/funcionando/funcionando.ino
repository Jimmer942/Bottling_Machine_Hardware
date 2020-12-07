int relay_2 = 15; // Sets the control pin for the relay in 15
int relay_1 = 2; // Sets the control pin for the relay in 2
const int sensorObj = 23; // Sets the sensing pin to 36
bool flag = LOW;
bool value;


TaskHandle_t Motor_Handle;
TaskHandle_t Object_Handle;
TaskHandle_t Relay_Handle;

void setup()
{
  Serial.begin(115200);
  pinMode(relay_2, OUTPUT); //Sets the GPIO pin 15 to OUTPUT
  pinMode(relay_1, OUTPUT); //Sets the GPIO pin 2 to OUTPUT
  pinMode(sensorObj, INPUT);  //Sets the GPIO pin 23 to INPUT

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
    value = digitalRead(sensorObj);  //lectura digital de pin
    if (value == LOW && flag == LOW) {
      Serial.println("Detectado obstaculo");
      digitalWrite(relay_1, HIGH);
      vTaskResume(Relay_Handle);
      vTaskSuspend(NULL);
    }
    flag = !value;
    delay(100);
  }
  vTaskDelete( NULL );
}

// This function will be invoked a task thta will make the motor run
void MoveMotor(void *param) {
  for (;;) {
    Serial.println("Motor is running");
    digitalWrite(relay_1, HIGH);
    if (value == HIGH){
      digitalWrite(relay_1, LOW);
    }
  }
  vTaskDelete( NULL );
}


void ActRelay(void *params) {
  for (;;) {
    // digitalWrite(relay, HIGH); // envia señal alta al relay
    Serial.println("Valvula abierta");
    digitalWrite(relay_2, LOW);
    delay(2500);           // 1 segundo
    digitalWrite(relay_2, HIGH);  // envia señal baja al relay
    Serial.println("Valvula Cerrada");
    delay(10);// 0.01 segundo|<a|    
    vTaskResume(Object_Handle);
    vTaskSuspend(NULL);
  }
  vTaskDelete( NULL );
}
