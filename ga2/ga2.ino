#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdio.h>

const uint8_t DHT11PIN =14;
 int cnt=0;
   int dt[82]={0,};

unsigned long long lastUs=0;
unsigned long long lastMMs=0;
unsigned long long lastUUs=0;
unsigned long long startUs=0;

int readTemp=0;
int readHumid=0;
int t=0;
int n=0;
int data=0;
void setup()
{
   Serial.begin(74880);
   
   
}

ICACHE_RAM_ATTR void ReadytoRead0(){
  Serial.printf("inter1\r\n");
  return;
}
/*
ICACHE_RAM_ATTR void ReadytoRead1(){
  Serial.printf("inter2\r\n");
 return;
}
*/

void loop()
{  
   cnt=0;
   dt[82]={0,};
   digitalWrite(DHT11PIN, 1);
   pinMode(DHT11PIN, OUTPUT);
   delay(1);
   digitalWrite(DHT11PIN, 0);
   delay(20);
   pinMode(DHT11PIN, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), ReadytoRead0, FALLING);
   dt[cnt*2] = micros();
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), ReadytoRead0, RISING);
   dt[cnt*2+1] = micros()-dt[cnt*2];
 
         cnt++;
        for(cnt =0; cnt<41; cnt++)
   {
      Serial.printf("cnt[%d] = %d\r\n",cnt,dt[cnt*2+1]);
   }
        
      
}
