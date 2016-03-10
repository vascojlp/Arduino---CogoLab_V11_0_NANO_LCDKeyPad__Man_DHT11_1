void Humidade() {

  DHT.read11(DHT11sensorPin);
  HM_value = DHT.humidity ;
  delay(50);
  DHT.read11(DHT11sensorPin);
  HM_value = DHT.humidity ;
  delay(50);
  
  lcd.clear();                           //Situamos o cursor no caracter 0, linha 0
  Serial.print(F("HUMIDADE INC. #1"));
  lcd.print(F("HUMIDADE INC. #1"));
  lcd.setCursor(0, 1);
  if (HM_value <= 0 || HM_value > 100) {
    lcd.print(F("ERROR !!!"));
    delay(3000);
  }
  else {
    Serial.print(HM_value);
    lcd.print(HM_value);
    lcd.print(F("   (%)"));
    Serial.print(F("\n"));
    Serial.print(F("  \n"));
    delay(3000);
  }

/************** Humidade arca *********************/
  DHT.read11(DHT11sensorPin1);
  HMA_value = DHT.humidity ;
  delay(50);
  DHT.read11(DHT11sensorPin1);
  HMA_value = DHT.humidity ;
  delay(50);

  lcd.clear();                           //Situamos o cursor no caracter 0, linha 0
  Serial.print(F("HUMIDADE INC. #3"));
  lcd.print(F("HUMIDADE INC. #3"));
  lcd.setCursor(0, 1);
  if (HMA_value <= 0 || HMA_value > 100) {
    lcd.print(F("ERROR !!!"));
    delay(3000);
  }
  else {
    lcd.print(HMA_value);
    lcd.print(F("   (%)"));
    delay(3000);
  }

}















