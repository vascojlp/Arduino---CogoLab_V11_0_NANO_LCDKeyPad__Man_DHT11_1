void Sensor_Luz() {
  /*
  Totalmente noite - 1000
  Entardecer - 736
  Dia de Chuva - 472
  Sol - 20
  */

  //PARA TESTES
  delay(50);
  LI_val = analogRead(A3);
  delay(50);
  LI_val = analogRead(A3);
  delay(50);
  Lux = map(LI_val, 0, 1023, 10000, 0);
  delay(50);

  if (stateIl == 1) {
    if (Lux <= 300) {

      lcd.clear();
      lcd.print(F("ILUMINACAO EM..."));
      lcd.setCursor(0, 1);
      lcd.print(F("...MODO AUTO!"));
      delay(500);
      digitalWrite(RL2LIpowerPin, LOW);
      currentMillisIl = millis();
      delay (360000);      //6 horas
      digitalWrite(RL2LIpowerPin, HIGH);
    }
  } else {
    digitalWrite(RL2LIpowerPin, HIGH);
  }
}

