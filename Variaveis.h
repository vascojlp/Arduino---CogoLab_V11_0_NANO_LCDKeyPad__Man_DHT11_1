int HM_value;
int TPA_value;

int HMA_value;
int TPAA_value;

int H;
int Hr;

float samples[10]; 
float valorLido = 0;
float temperatura = 0;


int state = LOW;      // the current state of the output pin
int previous = LOW;    // the previous reading from the input pin
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

int adc_key_in;
int k;
unsigned long currentMillis = 0;
unsigned long currentMillisVT = 0;

int btstate = 0;
int btstateRg = 0;

int Lux;
int EEsize = 1024;

int stateIl;
int stateRg;
int stateVt = 1;
unsigned long t = 0;
unsigned long a = 0 ;
unsigned long I = 0;
unsigned long Int = 0;
unsigned long Il = 0;
unsigned long Ilm = 0;
unsigned long Vt = 0;
unsigned long Vtm = 0;

float temp;


//--- Sensor de Iluminacao
int LI_min = 200;
float LI_val;

//--- Correr ILUMINACAO so 1x por dia
unsigned long currentMillisIl = 0;











