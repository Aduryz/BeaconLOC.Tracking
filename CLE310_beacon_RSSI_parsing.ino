#include <SoftwareSerial.h>
 
SoftwareSerial BSerial(2, 3); //TX to 2, RX to 3

String val;

String pink;
String pinkR;
int headP;
int tailP;
int headPR;
int tailPR;
int pinkP = 0;
String orange;
String orangeR;
int headO;
int tailO;
int headOR;
int tailOR;
int orangeP = 0;
String yellow;
String yellowR;
int headY;
int tailY;
int headYR;
int tailYR;
int yellowP = 0;

void setup()  {
  Serial.begin(9600);
  Serial.println("Hello!");
  BSerial.begin(9600);

  delay(1000);  // 꼭 있어야함
  BSerial.println("AT+SCAN"); //beacon scan
}
 
void loop(){
  if (BSerial.available()){
    String val = BSerial.readString();
    Serial.print("I received: ");
    Serial.println(val);  //beacon scan value
    delay(100);
    
    while(pinkP==0){  //parsing
      headP = val.indexOf("74:F0:7D:1A:02:C8");
      while (tailP < headP){
        tailP = val.indexOf("]", tailP+1);
      } 
      pink = val.substring(headP, tailP);

      while (headPR<tailP){
          headPR = val.indexOf("RSSI", headPR+1);
      }
      while (tailPR < headPR){
        tailPR = val.indexOf("]", tailPR+1);
      }
      pinkR = val.substring(headPR+5, tailPR);

      Serial.print("pinkR: ");
      Serial.println(pinkR);
      if (pink=="74:F0:7D:1A:02:C8"){
        pinkP = 1;
      }
    }

    while(orangeP==0){
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

      Serial.print("orangeR: ");
      Serial.println(orangeR);
      if (orange=="74:F0:7D:1A:02:A5"){
        orangeP = 1;
      }
    }

    while(yellowP==0){
      headY = val.indexOf("74:F0:7D:1A:02:E8");
      while (tailY < headY){
        tailY = val.indexOf("]", tailY+1);
      } 
      yellow = val.substring(headY, tailY);

      while (headYR<tailY){
          headYR = val.indexOf("RSSI", headYR+1);
      }
      while (tailYR < headYR){
        tailYR = val.indexOf("]", tailYR+1);
      }
      yellowR = val.substring(headYR+5, tailYR);

      Serial.print("yellowR: ");
      Serial.println(yellowR);
      if (yellow=="74:F0:7D:1A:02:E8"){
        yellowP = 1;
      }
    }
  }
}
