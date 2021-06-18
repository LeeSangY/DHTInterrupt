#define DHT11PIN 14
#include <Ticker.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
HTTPClient myClient;
unsigned long long lastMs=0;
float temp =0;
int flag=0;
int dt[82]={0,};
int readTemp;
int readHumid;
int cnt=0;
void printCountUS();
int counterUS;
Ticker timer(printCountUS, 100, 0, MICROS_MICROS); 

void printCountUS() {
  counterUS++;  
  if (counterUS == 10000) {
    Serial.println("10000 * 100us");
    counterUS = 0;
    }
  }
  
void setup() {

  Serial.begin(74880);
  timer.start();
}

ICACHE_RAM_ATTR void Ready(){
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), phase2, RISING);
}

ICACHE_RAM_ATTR void phase2()
{
 
}

int readDHT11(int *readTemp, int *readHumid)
{
  int dt[80]={0,};
  digitalWrite(DHT11PIN, 1);
  pinMode(DHT11PIN, OUTPUT);
  delay(1);
  digitalWrite(DHT11PIN, 0);
  delay(20);
  pinMode(DHT11PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Ready, FALLING);
  //attachInterrupt(digitalPinToInterrupt(DHT11PIN), Ready, RISING);
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), phase2, FALLING);
  
  for (cnt=0; cnt<38; cnt++)
  {
    dt[cnt*2]= micros();
    while(1)
    if(digitalRead(DHT11PIN) == 1) break;
    dt[cnt*2]= micros() - dt[cnt];
    
    dt[cnt*2+1] = micros();
    while(1)
    if(digitalRead(DHT11PIN) == 0) break;
    dt[cnt*2+1] = micros() - dt[cnt*2+1];
  }

    
    *readHumid = 0; 
    *readTemp = 0;
  


  
  for(cnt=1;cnt<9;cnt++) //Humid
  { 
    *readHumid = *readHumid<<1;
    if( dt[cnt*2+1]>49)
    {
      *readHumid = *readHumid +1 ;
    }
    else 
    {
      *readHumid = *readHumid +0 ;
    }
  }
  for(cnt=17;cnt<25;cnt++) //Temp
  { 
    *readTemp = *readTemp<<1;
     if( dt[cnt*2+1]>49)
    {
      *readTemp = *readTemp +1 ;
    }
    else 
    {
      *readTemp = *readTemp +0 ;
    }
  }
   return 1;
}

void loop() {

 timer.update();
  readDHT11(&readTemp, &readHumid)
   timer.interval(5500); 
  Serial.printf("Temp: %d, Humid: %d\r\n",readTemp, readHumid);
 
   
}
