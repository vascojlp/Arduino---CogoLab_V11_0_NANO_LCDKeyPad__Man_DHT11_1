void Prog_Ventilacao(){
  
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("-PROGRAMACAO-"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-VENTILACAO-  "));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  lcd.print(stateVt);
  lcd.setCursor(5, 2);

  if (stateVt == 1 ) {
    lcd.print("VENTILACAO ON");
  } else {
    lcd.print("VENTILACAO OFF");
  }


  while (btstate == 1) {

    delay(200);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      stateVt = 1;
      EEPROM.write(50, stateVt);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(stateVt);
      lcd.setCursor(3, 2);
      lcd.print("-VENT. ON");
      delay(10);
    }

    delay(200);
    //btnDOWN
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      stateVt = 0;
      EEPROM.write(50, stateVt);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(stateVt );
      lcd.setCursor(3, 2);
      lcd.print("-VENT. OFF");
      delay(10);
    }

    //btnSELECT
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 650 && adc_key_in < 850) {
      stateVt = 1 ;
      EEPROM.write(50, stateVt);
      delay(10);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("ESTADO ACTUAL:"));
      lcd.setCursor(0, 2);
      lcd.print(stateVt );
      lcd.setCursor(3, 2);
      lcd.print("-VENT. ON");

    }

    //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      lcd.clear();     
      lcd.print(F("ESTADO ACTUAL:"));    
      lcd.setCursor(0, 2);
      lcd.print(stateVt);
      if (stateVt == 1 ) {
        lcd.setCursor(5, 2);
        lcd.print("VENT. ON");
      } else {
        lcd.print("VENT. OFF");
      }
      delay(2000);
      btstate = 0 ;

    }
  }
  
  /*************** PROGRAMACAO TEMPO DE VENTILACAO **************************/
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TEMPO ACTUAL:"));
  lcd.setCursor(0, 2);
  EEPROM.read(Vt);
  lcd.print(Vt);
  lcd.setCursor(5, 2);
  lcd.print(F("(minutos)"));
  delay(2000);
  
  btstate = 1;
  while (btstate == 1) {
    delay(150);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      Vt = Vt + 1;
      EEPROM.write(60, Vt);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(Vt);
    }

    //btnDOWN
    delay(150);
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      Vt = Vt - 1;
      EEPROM.write(60, Vt);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(Vt);
    }

    //btnSELECT
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 650 && adc_key_in < 850) {
      Vt = 1;   
      EEPROM.write(60, Vt);
      delay(50);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TEMPO ACTUAL:"));
      EEPROM.read(Vt);
      lcd.setCursor(0, 2);
      lcd.print(Vt);
      lcd.setCursor(5, 2);
      lcd.print(F("(minutos)"));
    }

    //btnRIGHT - GRAVAR e sair
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      EEPROM.read(Vt);
      delay(50);
      if (Vt <= 0 ) {
        Vt = 1;
        EEPROM.write(60, Vt);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.Vent.<= 0"));
        delay (4000);
      }

      lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
      lcd.print(F("FIM PROGRAMACAO"));
      lcd.setCursor(0, 1);
      delay(2000);
      lcd.clear();
      lcd.print(F("TMP.VENT.ACTUAL:"));
      EEPROM.read(Vt);
      lcd.setCursor(0, 2);
      lcd.print(Vt);
      lcd.setCursor(5, 2);
      lcd.print(F("(minutos)"));
      delay(4000);
      btstate = 0 ;
    }
  }
   
  
}
