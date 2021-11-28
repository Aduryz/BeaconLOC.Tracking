String orange;
String orangeR;
int headO;
int tailO;
int headOR;
int tailOR;

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
  
  String val = "z-5+SCANNINGBT_ADDR[74:F0:7D:1A:02:A5],TX_PWR=[-2],RSSI[-63],NAME=[BoT]BT_ADDR[24:E8:53:1A:AE:A7],RSSI[-78]BT_ADDR[67:19:BA:8B:20:43],16BIT_UUID=[0xfd69],RSSI[-93]";

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

void loop(){

}
