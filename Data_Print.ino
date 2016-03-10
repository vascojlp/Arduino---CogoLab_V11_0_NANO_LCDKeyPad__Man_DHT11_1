void Data_Print()
{
  
  delay(50);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);
  delay(50);
  
  DateTime now = RTC.now();
  delay(250);
  lcd.begin(16, 2);
  delay(250);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("-- ALARME ON --"));
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(F("-- ALARME ON --"));
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(F("-- ALARME ON --"));
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(F("-- ALARME ON --"));
  delay(500);
  
  Keypad();
  
  lcd.clear();
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.setCursor(0, 1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  delay(3000);

  Keypad();
  
  lcd.clear();
  for(int i = 0; i<16; i++){
    lcd.setCursor(i, 0);
    lcd.print(F("*"));
    delay(100);
    }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("----- REGA -----"));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  stateRg = EEPROM.read(20);  // estado sensor rega
  lcd.print(stateRg);
  lcd.setCursor(5, 2);
  if (stateRg == 1 ) {
    lcd.print("Rega ON");
  } else {
    lcd.print("Rega OFF");
  }
  delay(3000);

  Keypad();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TEMPO REGA:"));
  lcd.setCursor(0, 2);
  stateRg = EEPROM.read(20);  // estado sensor rega
  a = EEPROM.read(a);         //tempo de rega
  lcd.print(t);
  lcd.setCursor(5, 2);
  lcd.print(F("(Segundos)"));
  delay(3000);

  Keypad();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("INTERVALO REGA:"));
  lcd.setCursor(0, 2);
  I = EEPROM.read(30);        //intervalo de rega
  lcd.print(I);
  lcd.setCursor(5, 2);
  lcd.print(F("(Minutos)"));
  delay(3000);
  
  Keypad();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("LAST EVENT RG:"));
  lcd.setCursor(0, 2);
  lcd.print (EEPROM.read(100));
  lcd.setCursor(3, 2);
  lcd.print(F("/"));
  lcd.setCursor(4, 2);
  lcd.print (EEPROM.read(110));
  lcd.print(F(" "));
  lcd.setCursor(10, 2);
  lcd.print (EEPROM.read(130));
  lcd.setCursor(12, 2);
  lcd.print(F(":"));
  lcd.setCursor(13, 2);
  lcd.print (EEPROM.read(140));
  delay(3000);

  Keypad();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("---ILUMINACAO---"));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  stateIl = EEPROM.read(10);  //estado sensor iluminacao
  lcd.print(stateIl);
  lcd.setCursor(5, 2);
  if (stateIl == 1 ) {
    lcd.print("-Ilum. ON");
  } else {
    lcd.print("-Ilum. OFF");
  }
  delay(3000);

  Keypad();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("VAL. ILUMINACAO:"));
  lcd.setCursor(0, 2);
  lcd.print(Lux);
  lcd.setCursor(5, 2);
  lcd.print("LUXs");
  delay(3000);

  Keypad();
  
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(F("LAST EVENT:"));
  lcd.setCursor(0, 2);
  lcd.print (EEPROM.read(150));
  lcd.setCursor(3, 2);
  lcd.print(F("/"));
  lcd.setCursor(4, 2);
  lcd.print (EEPROM.read(160));
  lcd.setCursor(6, 2);
  lcd.print(F("/"));
  lcd.setCursor(7, 2);
  lcd.print (EEPROM.read(170));
  lcd.setCursor(9, 2);
  lcd.print(F(" "));
  lcd.setCursor(10, 2);
  lcd.print (EEPROM.read(180));
  lcd.setCursor(12, 2);
  lcd.print(F(":"));
  lcd.setCursor(13, 2);
  lcd.print (EEPROM.read(190));
  delay(3000);
  
  Keypad();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("---VENTILACAO---"));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  stateRg = EEPROM.read(50);  // estado sensor rega
  lcd.print(stateVt);
  lcd.setCursor(5, 2);
  if (stateVt == 1 ) {
    lcd.print("Vent. ON");
  } else {
    lcd.print("Vent. OFF");
  }
  delay(3000);

  Keypad();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TEMPO VENT.:"));
  lcd.setCursor(0, 2);
  EEPROM.read(60);  // estado sensor rega
  EEPROM.read(Vt);         //tempo de rega
  lcd.print(Vt);
  lcd.setCursor(5, 2);
  lcd.print(F("(Minutos)"));
  delay(3000);

  Keypad();  
  
  lcd.clear();
  for(int i = 0; i<16; i++){
    lcd.setCursor(i, 0);
    lcd.print(F("*"));
    delay(100);
    }
}






