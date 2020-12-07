int relay = 15;

void setup() {
  // Configuración
  pinMode(relay, OUTPUT); // Configurar relay como salida o OUTPUT
  Serial.begin(9600); // Abrir el puerto serie a la velocidad de 9600bps para trasnmicion de datos.
}

void loop() {
  // Código principal donde ocurren en loop
   // envia señal alta al relay
   digitalWrite(relay, HIGH);
}
