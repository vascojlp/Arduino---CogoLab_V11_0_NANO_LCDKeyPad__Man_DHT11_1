

/////  OK COM KEYPAD, VENTILACAO MANUAL E AUTO, PROGRAMAÇÃO DE TEMPO DE REGA, ILUMINAÇÃO !!!

//--- BIBLIOTECAS
#include <LiquidCrystal.h>
#include <dht.h>
#include <Wire.h>
#include <RTClib.h>
#include "Variaveis.h"
#include <Event.h>
#include <Timer.h>
#include <EEPROM.h>

//--- Inicializacao dos Sensores
dht DHT;
RTC_DS1307 RTC;

//--- DEFINICAO DE PINOS
// Analog Pins
#define DHT11sensorPin A1       // Input Humidity sensor and Air temperature 
#define DHT11sensorPin1 A6       // Input Humidity sensor and Air temperature Arca
#define LIsensorPin A3         // Input Light photocell sensor
#define pinoSensor  A2

// digital pins
#define RL1WSRpowerPin 2       // power Output to eletrovÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¡lvula da Rega 
#define RL2LIpowerPin 3        // Iluminacao
#define RL3VTpowerPin  4        //Ventilacao arca
//#define RL4powerPin  5

// select the pins used on the LCD panel - TENHO DE ALTERAR OS PINOS (O D4 E D5 SAO O sda E scl)
/*Pins used by LCD & Keypad Shield:

    A0: Buttons, analog input from voltage ladder

    D4: LCD bit 4 --> D11: LCD bit 4
    D5: LCD bit 5 --> D10: LCD bit 5
    D6: LCD bit 6 --> D9: LCD bit 6
    D7: LCD bit 7 --> D8: LCD bit 7
    D8: LCD RS    --> D12: LCD RS
    D9: LCD E     --> D13: LCD E

    D3: LCD Backlight (high = on, also has pullup high so default is on) */

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); (RS,E,DB4,DB5,DB6,DB7)
//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) - create a new LiquidCrystal object using a 4 bit data bus
//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7) - createa new LiquidCrystal object using an 8 bit data bus
LiquidCrystal lcd(12, 13, 11, 10, 9, 8);

//--- KEYPAD
// define some values used by the panel and buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//--- RTC - Definicao Chars
const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

//--- VOID SETUP
void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);

  // Inicializacao do RTC
  Wire.begin();
  RTC.begin();

  //--- BOOT

  lcd.setCursor(0, 0);                 //Situamos o cursor no caracter 0, linha
  lcd.print(F("BOOTING..."));
  delay(1000);
  lcd.clear();
  lcd.print(F("BOOTING......"));
  delay(1000);
  lcd.clear();
  lcd.print(F("BOOTING........."));
  delay(1000);
  lcd.clear();
  lcd.print(F("COGOLAB V11.0 #1"));
  lcd.setCursor(0, 1);
  lcd.print(F("*NOT MULTITASK*"));
  delay(2000);

  stateIl = EEPROM.read(10);  //estado sensor iluminacao
  delay(50);
  stateRg = EEPROM.read(20);  // estado sensor rega
  delay(50);
  I = EEPROM.read(30);        //intervalo de rega
  delay(50);
  Il = EEPROM.read(40);      //tempo iluminacao manual
  t = EEPROM.read(1);         //tempo de rega
  delay(50);
  
  EEPROM.read(Vt);
  delay(50);
  if (Vt <= 0 ) {
  Vt = 3;
  EEPROM.write(60, Vt);
  delay(50);
  }

  //--- DESMARCAR PARA ACERTAR A HORA
  Acertar_Hora();

  //--- Analog pins
  pinMode(DHT11sensorPin, INPUT);
  pinMode(DHT11sensorPin1, INPUT);

  //--- Digital pins
  digitalWrite(RL1WSRpowerPin, HIGH);
  pinMode(RL1WSRpowerPin, OUTPUT);

  digitalWrite(RL2LIpowerPin, HIGH);
  pinMode(RL2LIpowerPin, OUTPUT);
  
  digitalWrite(RL3VTpowerPin, HIGH);
  pinMode(RL3VTpowerPin, OUTPUT);
  
  //digitalWrite(RL4powerPin, HIGH);
  //pinMode(RL4powerPin, OUTPUT);
}

//--- VOID LOOP
void loop() {
  
  delay(50);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);
  delay(50);
  
  //--- ACERTAR DATA E HORA
  //btnDOW
  adc_key_in = 0;
  adc_key_in = analogRead(0);    // read the value from the sensor
  if (adc_key_in > 250 && adc_key_in < 450) {
    Acertar_Hora();
  } else {};

  Data_Print();
  Keypad();
  Temperatura_Incubacao();
  Keypad();
  Humidade();
  Keypad();
  Rega();
  
  delay(50);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);
  
  Keypad();
  Sensor_Luz();
  
  delay(50);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);
  
  Keypad();
  Ventilacao();
  
  delay(50);
  lcd.begin(16, 2);                    // start the library
  lcd.setCursor(0, 0);
}

//--- FIM VOID LOOP
byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}
byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

//---
void setTime() {

  Serial.print(F("Please enter the current year, 00-99. - "));
  year = readByte();
  Serial.println(year);
  Serial.print(F("Please enter the current month, 1-12. - "));
  month = readByte();
  Serial.println(months[month - 1]);
  Serial.print(F("Please enter the current day of the month, 1-31. - "));
  monthday = readByte();
  Serial.println(monthday);
  Serial.println(F("Please enter the current day of the week, 1-7."));
  Serial.print(F("1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - "));
  weekday = readByte();
  Serial.println(days[weekday - 1]);
  Serial.print(F("Please enter the current hour in 24hr format, 0-23. - "));
  hour = readByte();
  Serial.println(hour);
  Serial.print(F("Please enter the current minute, 0-59. - "));
  minute = readByte();
  Serial.println(minute);
  second = 0;
  Serial.println(F("The data has been entered."));

  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}

byte readByte() {
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}

//---
void printTime() {
  char buffer[3];
  readTime();
  Serial.print(days[weekday - 1]);
  Serial.print(F(" "));
  Serial.print(months[month - 1]);
  Serial.print(F(" "));
  Serial.print(monthday);
  Serial.print(F(", 20"));
  Serial.print(year);
  Serial.print(F(" "));
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(days[weekday - 1]);
  lcd.print(F(" "));
  lcd.print(months[month - 1]);
  lcd.print(F(" "));
  lcd.print(monthday);
  lcd.print(F(", 20"));
  lcd.print(year);
  lcd.print(F(" "));
  
  Serial.print(hour);
  Serial.print(F(":"));
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  
  lcd.setCursor(7,1);
  lcd.print(hour);
  lcd.print(F(":"));
  sprintf(buffer, "%02d", minute);
  lcd.print(buffer);
}

//---
void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

//--- FIM  DO PROGRAMA








