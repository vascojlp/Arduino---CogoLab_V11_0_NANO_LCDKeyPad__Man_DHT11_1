void Rega() {

  DateTime myRTC = RTC.now();
  Hr = (myRTC.hour());

  stateRg = EEPROM.read(20);  // estado sensor rega
  delay(50);
  I = EEPROM.read(30);        //intervalo de rega
  delay(50);
  a = EEPROM.read(1);         //tempo de rega
  delay(50);

  Int = I * 60 * 1000; //milisegundos
  delay(50);
  a = t * 1000;        //milisegundos
  delay(50);

  if ( stateRg == 1) {
    if (H >= 8 && H <= 21 && currentMillis <= 5000) {     //3600000 = 1 hora
      lcd.clear();
      lcd.print(F("REGA EM..."));
      Serial.print(F("REGA EM..."));
      lcd.setCursor(0, 1);
      lcd.print(F("...MODO AUTO!"));

      digitalWrite(RL1WSRpowerPin, LOW);
      delay(a);
      currentMillis = millis();

      DateTime now = RTC.now();
      EEPROM.write(100, now.day());
      EEPROM.write(110, now.month());
      EEPROM.write(120, now.year());
      EEPROM.write(130, now.hour());
      EEPROM.write(140, now.minute());

      digitalWrite(RL1WSRpowerPin, HIGH);
      delay(500);
    } else {
      digitalWrite(RL1WSRpowerPin, HIGH);
      delay(500);
    }

    if (H >= 8 && H <= 21 && currentMillis + Int <= millis() ) {
      lcd.clear();
      lcd.print(F("REGA EM..."));
      lcd.setCursor(0, 1);
      lcd.print(F("...MODO AUTO!"));

      digitalWrite(RL1WSRpowerPin, LOW);
      delay(a);                                                     // 5 minutos
      currentMillis = millis();

      DateTime now = RTC.now();
      EEPROM.write(100, now.day());
      EEPROM.write(110, now.month());
      EEPROM.write(120, now.year());
      EEPROM.write(130, now.hour());
      EEPROM.write(140, now.minute());
      digitalWrite(RL1WSRpowerPin, HIGH);
      delay(1000);

    }
    else {
      digitalWrite(RL1WSRpowerPin, HIGH);

    }

  }
}

