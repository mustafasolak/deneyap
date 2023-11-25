#define solSensor A0
#define ortaSensor A1
#define sagSensor A2
int solSensorDegeri, ortaSensorDegeri, sagSensorDegeri;
void setup() {
  pinMode(solSensor, INPUT);
  pinMode(ortaSensor, INPUT);
  pinMode(sagSensor, INPUT);

  Serial.begin(115200);
  Serial.println("Program başladı..");
}

void loop() {
  // Sensörlerden gelen verileri okuyoruz
  solSensorDegeri = analogRead(solSensor);
  ortaSensorDegeri = analogRead(ortaSensor);
  sagSensorDegeri = analogRead(sagSensor);
  // Sensörlerden okunan değerler ekrana yazdırılıyor
  Serial.print("Sol sensor :");
  Serial.println(solSensorDegeri);
  Serial.print("Orta sensor :");
  Serial.println(ortaSensorDegeri);
  Serial.print("Sağ sensor :");
  Serial.println(sagSensorDegeri);
  
  Serial.println("\n\n");
  delay(100);
}
