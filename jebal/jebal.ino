#define DHT11PIN 14
#include <Ticker.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
HTTPClient myClient;
unsigned long long lastMs=0;
float temp =0;
Ticker Timer;
volatile int dt[82]={0,};
volatile int data[82]={0,};
int readTemp;
int readHumid;
volatile int cnt=0;
volatile int t=0;
int i=0;
void setup() {

  Serial.begin(74880);

}

ICACHE_RAM_ATTR void collector0(){
  dt[cnt] = micros();
   cnt++;
}

ICACHE_RAM_ATTR void collector1(){
 dt[cnt] = micros();
    cnt++;
   
}
void timeout(){
  if(data[i]>2000)
     return 0;
}
int readDHT11(int *readTemp, int *readHumid)
{
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), collector0, FALLING);
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), collector1, RISING);
  
  
  digitalWrite(DHT11PIN, 1);
  pinMode(DHT11PIN, OUTPUT);
  delay(1);
  digitalWrite(DHT11PIN, 0);
  delay(20);
  pinMode(DHT11PIN, INPUT_PULLUP);
   
     *readHumid = 0; 
     *readTemp = 0;
    for(int i =0; i<40;i++)
    {
      data[i]=dt[i+1]-dt[i];
      //Serial.printf("cnt = %d, dt[cnt] = %d, %d, data = %d\r\n",i, dt[i],dt[i+1],data[i]);
      if(Timer.attach(1, timeout))
      {
        break;
      }
    }
    cnt=0;
    
  for(t=1;t<9;t++) //Humid
  { 
    *readHumid = *readHumid<<1;
    if( data[t]>100)
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
     if( data[t]>100)
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
  dt[82]={0,};
  data[82]={0,};
 
}
