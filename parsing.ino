String orange;
String orangeR;
int headO;
int tailO;
int headOR;
int tailOR;

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
  
  String val = "BT_ADDR[74:F0:7D:1A:02:E8],TX_PWR=[-2],RSSI[-51],NAME=[BoT] BT_ADDR[74:F0:7D:1A:02:A5],TX_PWR=[-2],RSSI[-48],NAME=[BoT] BT_ADDR[74:F0:7D:1A:02:C8],TX_PWR=[-2],RSSI[-57],NAME=[BoT]";
  
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
