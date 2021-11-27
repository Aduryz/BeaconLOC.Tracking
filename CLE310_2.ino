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
  delay(100);
  long b=BSerial.read();
  Serial.println("b");
  //Serial.println(b);  
  delay(100);
  toChar();
}
 
void loop(){
  if (BSerial.available()){
    Serial.write(BSerial.read());
  }
  if (Serial.available()){
    BSerial.write(Serial.read());
  }
}

void toChar(){
  char c = (char)b;
  delay(100);
  toString();
}

void toString(){
  delay(100);
  String val = String(c);
  delay(100); 
  Serial.println("val");
  Serial.println(val);
  delay(100);
  a = 1;
  delay(100);
  parsing(); 
}

void parsing(){
  if (a ==1){
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
  Serial.println(headO);
  Serial.println(tailO);
  Serial.println(orangeR);
  Serial.println(headOR);
  Serial.println(tailOR);
  }
}
