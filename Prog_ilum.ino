void Prog_ilum() {

  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("--PROGRAMACAO--"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("---ILUMINACAO---"));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  lcd.print(stateIl);
  lcd.setCursor(5, 2);

  if (stateIl == 1 ) {
    lcd.print("Ilum. ON");
  } else {
    lcd.print("Ilum. OFF");
  }


  while (btstate == 1) {

    delay(200);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      stateIl = 1;
      EEPROM.write(10, stateIl);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(stateIl );
      lcd.setCursor(3, 2);
      lcd.print("-Ilum. ON");
      delay(10);
    }

    delay(200);
    //btnDOWN
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      stateIl = 0;
      EEPROM.write(10, stateIl);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(stateIl );
      lcd.setCursor(3, 2);
      lcd.print("-Ilum. OFF");
      delay(10);
    }

    //btnSELECT
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 650 && adc_key_in < 850) {
      stateIl = 1 ;
      EEPROM.write(10, stateIl);
      delay(10);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("ESTADO ACTUAL:"));
      lcd.setCursor(0, 2);
      lcd.print(stateIl );
      lcd.setCursor(3, 2);
      lcd.print("-Ilum. ON");

    }

    //btnRIGHT - GRAVAR E SAIR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      lcd.clear();
      lcd.print(F("ESTADO ACTUAL:"));
      lcd.setCursor(0, 2);

      if (stateIl == 1 ) {
        lcd.print("Ilum. ON");
      } else {
        lcd.print("Ilum. OFF");
      }
      delay(4000);
      btstate = 0 ;

    }
  }
  
  /*************** PROGRAMACAO TEMPO DE ILUMINACAO **************************/
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TP.IL.MN.ACTUAL:"));
  lcd.setCursor(0, 2);
  EEPROM.read(t);
  lcd.print(Il);
  lcd.setCursor(5, 2);
  lcd.print(F("(Segundos)"));
  delay(2000);
  
  btstate = 1;
  while (btstate == 1) {
    delay(150);
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      Il = Il + 1;
      EEPROM.write(40, Il);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(Il);
    }

    //btnDOWN
    delay(150);
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      Il = Il - 1;
      EEPROM.write(40, Il);
      delay(50);
      lcd.setCursor(0, 2);
      lcd.print(Il);
    }

    //btnSELECT
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 650 && adc_key_in < 850) {
      Il = 60;    //10segundos
      EEPROM.write(40, Il);
      delay(50);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("EEPROM CLEARED!"));
      delay (2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TEMPO ACTUAL:"));
      EEPROM.read(Il);
      lcd.setCursor(0, 2);
      lcd.print(Il);
      lcd.setCursor(5, 2);
      lcd.print(F("(Segundos)"));
    }

    //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      EEPROM.read(Il);
      delay(50);
      if (Il <= 0 ) {
        Il = 60;
        EEPROM.write(40, Il);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.Ilum.<= 0"));
        delay (4000);
      }

      lcd.clear();
      lcd.print(F("TP.IL.MN.ACTUAL:"));
      EEPROM.read(Il);
      lcd.setCursor(0, 2);
      lcd.print(Il);
      lcd.setCursor(5, 2);
      lcd.print(F("(Segundos)"));
      delay(4000);
      btstate = 0 ;
    }
  }
  
/*********************** PROGRAMAÇÃO VENTILAÇÃO ************************/ 
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("--PROGRAMACAO--"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("---VENTILACAO---  "));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO VT.ACTUAL:"));
  lcd.setCursor(0, 2);
  lcd.print(stateVt);
  lcd.setCursor(5, 2);

  if (stateVt == 1 ) {
    lcd.print("VENTILACAO ON");
  } else {
    lcd.print("VENTILACAO OFF");
  }


  btstate = 1;
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
      lcd.print(" -VENT. ON");
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
      lcd.print(" -VENT. OFF");
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
      lcd.print(" -VENT. ON");

    }

    //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {

      lcd.clear();     
      lcd.print(F("ESTADO VT.ACTUAL:"));    
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
  lcd.print(F("TEMPO VT.ACTUAL:"));
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

lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
lcd.print(F("FIM PROGRAMACAO"));
lcd.setCursor(0, 1);
delay(2000);
  

}

