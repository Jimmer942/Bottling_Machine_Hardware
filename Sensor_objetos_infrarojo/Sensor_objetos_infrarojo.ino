const int sensorPin = 9;
bool flag = LOW;

void setup() {
  Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin );  //lectura digital de pin
  
  if (value == LOW && flag == LOW) {
      Serial.println("Detectado obstaculo");
  }
  flag = !value;
  delay(100);
}
