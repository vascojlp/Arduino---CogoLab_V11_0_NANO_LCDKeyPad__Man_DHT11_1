void Keypad()
{

  /*
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;
  */


  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor

  k = (analogRead(0) - adc_key_in);    //gives the button a slight range to allow for a little contact resistance


  //dOUBLE PRESS
  if (5 < abs(k)) {
  }

  //NO Press
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 1000) {
  }

  /****************** REGA MANUAL ********************/
  //btnSELECT
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 650 && adc_key_in < 850) {
    lcd.clear();
    lcd.print(F("NEBULIZADOR..."));
    lcd.setCursor(0, 1);
    lcd.print(F("MODO MANUAL!"));
    digitalWrite(RL1WSRpowerPin, LOW);
    delay(t * 1000);
    digitalWrite(RL1WSRpowerPin, HIGH);
    delay(1000);

  }
  /****************** PROGRAMACAO REGA ********************/
  //  btnLEFT
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 450 && adc_key_in < 650) {
    btstate = 1;
    Prog_Time ();
  }

  /****************** PROGRAMACAO ILUMINACAO ********************/
  //  btnRIGTH
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in < 50) {
    btstate = 1;
    Prog_ilum ();
  }

  /****************** ILUMINACAO MANUAL ********************/
  //btnUP
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 50 && adc_key_in < 250) {
    EEPROM.read(Il);
    Ilm = Il*1000;
    lcd.clear();
    lcd.print(F("iLUMINACAO EM..."));
    lcd.setCursor(0, 1);
    lcd.print(F("MODO MANUAL!"));
    digitalWrite(RL2LIpowerPin, LOW);
    digitalWrite(RL3VTpowerPin, LOW);
    delay(Ilm);
    digitalWrite(RL2LIpowerPin, HIGH);
  }

/****************** PROGRAMACAO VENTILACAO ********************/
 /*
  //  btnLEFT + select
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 850 && adc_key_in < 950) {
    btstate = 1;
    Prog_Ventilacao ();
  }
*/

}














