void Ventilacao() { 

  if (stateVt == 1) {
  DateTime myRTC = RTC.now();
  Hr = (myRTC.hour());
   
if (currentMillisVT <= 10000){   
      lcd.clear(); 
      lcd.print(F("VENTAX ON...")); 
      lcd.setCursor(0, 1);
      lcd.print(F("MODO AUTOMATICO!")); 
      digitalWrite(RL3VTpowerPin, LOW);
      delay(5000);
      currentMillisVT = millis();
      DateTime now = RTC.now();
      } else {
    digitalWrite(RL3VTpowerPin, HIGH); 
      delay(500); 
    }
    
 if (currentMillisVT + 3600000 <= millis() ){      //3600000 = 1 hora   
      lcd.clear(); 
      lcd.print(F("VENTAX ON..."));
      lcd.setCursor(0, 1);
      lcd.print(F("MODO AUTOMATICO!"));
      digitalWrite(RL3VTpowerPin, LOW);
      EEPROM.read(Vt);
      Vtm = Vt * 60 * 1000;
      delay(Vtm);
      currentMillisVT = millis();
    
      DateTime now = RTC.now(); 
      EEPROM.write(150, now.day()); 
      EEPROM.write(160, now.month()); 
      EEPROM.write(170, now.year());
      EEPROM.write(180, now.hour());
      EEPROM.write(190, now.minute());
    } else {
         digitalWrite(RL3VTpowerPin, HIGH); 
       delay(500);
     }
   
    } else {
         digitalWrite(RL3VTpowerPin, HIGH); 
       delay(500);
     }
        
 } 

