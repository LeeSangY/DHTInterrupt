#define DHT11PIN 14
#include <Ticker.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
HTTPClient myClient;
unsigned long long lastMs=0;
float temp =0;
int flag=0;
int dt[82]={0,};
int data[82]={0,};
int readTemp;
int readHumid;
int cnt=0;
int t=0;

void setup() {

  Serial.begin(74880);

}

ICACHE_RAM_ATTR void collector0(){
   dt[cnt*2] = micros()-dt[cnt];
   cnt++;
}

ICACHE_RAM_ATTR void collector1(){
   dt[cnt*2+1] = micros()-dt[cnt];
   cnt++;
}

int readDHT11(int *readTemp, int *readHumid)
{
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), collector0, FALLING);
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), collector1, RISING);
  int dt[1000]={0,};
  int data[1000]={0,};
  digitalWrite(DHT11PIN, 1);
  pinMode(DHT11PIN, OUTPUT);
  delay(1);
  digitalWrite(DHT11PIN, 0);
  delay(20);
  pinMode(DHT11PIN, INPUT_PULLUP);
  
  
  
  dt[cnt*2] = dt[cnt] - dt[cnt+1]
 
    *readHumid = 0; 
    *readTemp = 0;
    

  for(t=2;t<10;t++) //Humid
  { 
    *readHumid = *readHumid<<1;
    if( data[t]>49)
    {
      *readHumid = *readHumid +1 ;
    }
    else 
    {
      *readHumid = *readHumid +0 ;
    }
  }
  
  for(t=17;t<25;t++) //Temp
  { 
    *readTemp = *readTemp<<1;
     if( data[t]>49)
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

  readDHT11(&readTemp, &readHumid);
  delay(5500);
  Serial.printf("Temp: %d, Humid: %d\r\n",readTemp, readHumid);
 
}
