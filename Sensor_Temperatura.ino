void Temperatura_Incubacao() {

  DHT.read11(DHT11sensorPin);
  TPA_value = DHT.temperature;
  delay(50);
  
  DHT.read11(DHT11sensorPin1);
  TPAA_value = DHT.temperature;
  delay(50);

 for(int i = 1; i <= 10; i++) { // Gets 10 samples of temperature
     valorLido = analogRead(pinoSensor);
     samples[i] = (valorLido * 0.00488);
     temperatura = samples[i] * 100;
     temperatura = temperatura + samples[i]; 
     delay(50);
    }
    
  temperatura = temperatura/10;  
  
  /*valorLido = analogRead(pinoSensor);
  temperatura = (valorLido * 0.00488);
  temperatura = temperatura * 100;
*/

  DateTime myRTC = RTC.now();
  H = 0;
  H = (myRTC.hour());
  delay(50);

  /********** TEMPERATURA AMBIENTE NA COZINHA ************/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TEMP. COZINHA:"));
  lcd.setCursor(0, 2);
  lcd.print(temperatura);
  lcd.setCursor(5, 2);
  lcd.print(F("C."));
  delay(3000);

  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  Serial.print(F("TEMP. INC.#1"));
  lcd.print(F("TEMP. INC.#1"));
  lcd.setCursor(0, 1);
  if (TPA_value <= 0 || TPA_value >= 45) {
    lcd.print(F("ERROR !!!"));
    delay(3000);
  }
  else {
    Serial.print(TPA_value);
    lcd.print(TPA_value);
    lcd.print(F("   (C.)"));
    Serial.print(F("\n"));
    Serial.print(F("  \n"));
    delay(3000);
  }
  
  /*************** Temperatura Arca ******************/
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  Serial.print(F("TEMP. INC.#3"));
  lcd.print(F("TEMP. INC.#3"));
  lcd.setCursor(0, 1);
  if (TPAA_value <= 0 || TPAA_value >= 45) {
    lcd.print(F("ERROR !!!"));
    delay(3000);
  }
  else {
    Serial.print(TPAA_value);
    lcd.print(TPAA_value);
    lcd.print(F("   (C.)"));
    Serial.print(F("\n"));
    Serial.print(F("  \n"));
    delay(3000);
  }

  /*

  lcd.clear();
  lcd.print(F("TEMP. INCU. #1:"));
  lcd.setCursor(0, 1);
  lcd.print(TPA3_value);
  lcd.print(F(" Graus C."));
  delay(4000);
  */

}















