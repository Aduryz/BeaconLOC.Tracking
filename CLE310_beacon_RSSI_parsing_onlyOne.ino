#include <SoftwareSerial.h>
 
SoftwareSerial BSerial(2, 3); //TX to 2, RX to 3

String orange;
String orangeR;
int headO;
int tailO;
int headOR;
int tailOR;

long b;
char c;
String val;
int a = 0;

void setup()  {
  Serial.begin(9600);
  Serial.println("Hello!");
 
  // set the data rate for the BT port
  BSerial.begin(9600);

  delay(1000);  // 꼭 있어야함
  BSerial.println("AT+SCAN");
}
 
void loop(){
  if (BSerial.available()){
    String val = BSerial.readString();
    Serial.print("I received: ");
    Serial.println(val);
    delay(100);
    headO = val.indexOf("74:F0:7D:1A:02:A5");
    while (tailO < headO){
      tailO = val.indexOf("]", tailO+1);
    } 
    orange = val.substring(headO, tailO);

    while (headOR<tailO){
        headOR = val.indexOf("RSSI", headOR+1);
    }
    while (tailOR < headOR){
      tailOR = val.indexOf("]", tailOR+1);
    }
    orangeR = val.substring(headOR+5, tailOR);

    Serial.println(orange);
    Serial.println(orangeR);
    }
}
