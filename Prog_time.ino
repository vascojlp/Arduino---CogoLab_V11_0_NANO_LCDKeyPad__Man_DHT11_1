void Prog_Time() {

  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("- PROGRAMACAO -"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-- REGA --  "));
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  lcd.print(stateRg);
  lcd.setCursor(5, 2);
  if (stateRg == 1 ) {
    lcd.print("Rega ON");
  } else {
    lcd.print("Rega OFF");
  }
  delay(2000);

  /******************** PROGRAMACAO DO SENSOR ON-OFF *****************************/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Novo Estado:"));

  btstateRg = 1;
  while (btstateRg == 1) {
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      stateRg = 1;
      EEPROM.write(20, stateRg);
      lcd.setCursor(0, 2);
      lcd.print(stateRg);
      lcd.setCursor(3, 2);
      lcd.print("- Rega ON");
      btstateRg = 0;
      delay(2000);
    }

    //btnDOW
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      stateRg = 0;
      EEPROM.write(20, stateRg);
      lcd.setCursor(0, 2);
      lcd.print(stateRg);
      lcd.setCursor(3, 2);
      lcd.print("-Rega OFF");
      btstateRg = 0;
      delay(2000);
    }
  }

  /******************** PROGRAMACAO DO TEMPO DE REGA *****************************/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TEMPO ACTUAL:"));
  lcd.setCursor(0, 2);
  EEPROM.read(t);
  lcd.print(t);
  lcd.setCursor(5, 2);
  lcd.print(F("(Segundos)"));
  delay(2000);

  while (btstate == 1) {
    delay(200);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      t = t + 1;
      EEPROM.write(1, t);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(t);
    }

    //btnDOWN
    delay(200);
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      t = t - 1;
      EEPROM.write(1, t);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(t);
    }

    //btnSELECT
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 650 && adc_key_in < 850) {
      t = 3;    //10segundos
      EEPROM.write(1, t);
      delay(50);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TEMPO ACTUAL:"));
      EEPROM.read(t);
      lcd.setCursor(0, 2);
      lcd.print(t);
      lcd.setCursor(5, 2);
      lcd.print(F("(Segundos)"));
    }

    //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      EEPROM.read(t);
      delay(50);
      if (t <= 0 ) {
        t = 3;
        EEPROM.write(1, t);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.REGA <= 0"));
        delay (4000);
      }

      lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
      lcd.print(F("FIM PROGRAMACAO"));
      lcd.setCursor(0, 1);
      delay(2000);
      lcd.clear();
      lcd.print(F("TMP.REGA.ACTUAL:"));
      EEPROM.read(t);
      lcd.setCursor(0, 2);
      lcd.print(t);
      lcd.setCursor(5, 2);
      lcd.print(F("(Segundos)"));
      delay(4000);
      btstate = 0 ;
    }
  }

  /******************** PROGRAMAÃ‡ÃƒO DO INTERVALO DE TEMPO DE REGA *****************************/
  btstate = 1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("INT.REGA ATUAL:"));
  EEPROM.read(I);      //minutos
  lcd.setCursor(0, 2);
  lcd.print(I);
  lcd.setCursor(5, 2);
  lcd.print(F("(minutos)"));
  delay(2000);

  while (btstate == 1) {
    delay(200);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      I = I + 1;  //minutos
      EEPROM.write(30, I);
      lcd.setCursor(0, 2);
      lcd.print(I);
    }

    //btnDOWN
    delay(200);
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      I = I - 1;  //minutos
      EEPROM.write(30, I);
      lcd.setCursor(0, 2);
      lcd.print(I);
    }

    //btnSELECT - CLEAR EEPROM
    adc_key_in = 0;
    adc_key_in = analogRead(0);
    if (adc_key_in > 650 && adc_key_in < 850) {
      I = 60;
      EEPROM.write(30, I);
      delay(10);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("INT.REGA ATUAL:"));
      lcd.setCursor(0, 2);
      EEPROM.read(I);
      delay(50);
      lcd.print(I);
      lcd.setCursor(5, 2);
      lcd.print(F("(Minutos)"));
    }

    //btnRIGHT - GRAVAR E SAIR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    EEPROM.read(I);
    delay(50);
    if (adc_key_in < 50) {
      if (I <= 0 ) {
        I = 60;
        EEPROM.write(30, I);
        delay(50);
        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("Int <= 0Seg. "));
        delay (4000);
      }

      lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
      lcd.print(F("FIM PROGRAMACAO"));
      lcd.setCursor(0, 1);
      delay(2000);
      lcd.clear();
      lcd.print(F("INT.REGA ATUAL:"));
      EEPROM.read(I);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(I);
      lcd.setCursor(5, 2);
      lcd.print(F("(minutos)"));
      delay(4000);
      btstate = 0 ;
    }
  }

}



















