const int sensorPin = 36;
bool flag = LOW;

void setup() {
  Serial.begin(115200);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}

int value = 0;

void loop(){
  value = digitalRead(sensorPin );  //lectura digital de pin
  
  if (value == LOW && flag == LOW) {
      Serial.println("Detectado obstaculo");
  }
  flag = !value;
  delay(1);
}
