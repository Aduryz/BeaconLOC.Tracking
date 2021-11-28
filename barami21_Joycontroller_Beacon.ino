#include <SoftwareSerial.h>
SoftwareSerial RFSerial(2, 3); //TX to 2, RX to 3

#include <LiquidCrystal_I2C.h>

char xPin = A0;  //joystick
char yPin = A1;
char zPin = 8;
int buttonPin = 7;

int xValue = 0;
int yValue = 0; 
int zValue = 0;
int buttonValue = 0;

char xSign = 0;
char ySign = 0;
int carStance = 0; // 자동차 on/off

int speed = 0;

long lastSend, now;  //RF send
char command;
String speedSend;
String sendString;
char send[100];

char location = 'U';  //vehicle location

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){ 
  Serial.begin(9600);
  RFSerial.begin(9600);
  pinMode(zPin,INPUT);    // 버튼 설정
  pinMode(buttonPin,INPUT);
  digitalWrite(zPin,HIGH);
  lcd.begin();
  lcd.backlight();
} 

void loop(){ 
  xValue = analogRead(xPin); 
  xValue = 1023-xValue;   // x축으로 보기 쉽게 변환(오른쪽으로 갈수록 커지게)
  yValue = analogRead(yPin);  
  zValue = digitalRead(zPin);
  buttonValue = digitalRead(buttonPin);
  delay(50);

  location = RFSerial.read();

  /*
  Serial.print(xValue,DEC);   // 시리얼 모니터에 값 표시
  Serial.print(",");
  Serial.print(yValue,DEC);
  Serial.print(",");
  Serial.print(!zValue);
  Serial.print("\n");
  Serial.print(carStance);
  Serial.print("\n");
  delay(50); 
  */

  if(zValue==0){
    if(carStance==0){
      carStance = 1;
      command = 'Y';
      delay(500);
    }
    else if(carStance==1){
      carStance = 0;
      command = 'N';
      delay(500);
    }
  }

  if(xValue>=550){    //x,y축 방향 판단
    xSign = 1;
  }
  else if(xValue<=470){
    xSign = -1;
  }
  else{
    xSign = 0;
  }
  if(yValue>=550){
    ySign = 1;
  }
  else if(yValue<=470){
    ySign = -1;
  }
  else{
    ySign = 0;
  }

  if(ySign==1 && xSign==0){   // forward
    speed = 470-(1023-yValue);
    speed = map(speed, 0, 470, 0, 255);
    
    command = 'F';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("forward");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==-1 && xSign==0){   // backward
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);

    command = 'B';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("backward");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==0 && xSign==1){   // right
    speed = 470-(1023-xValue);
    speed = map(speed, 0, 470, 0, 255);
    

    command = 'R';
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("right");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==0 && xSign==-1){   // left
    speed = 470-xValue;
    speed = map(speed, 0, 470, 0, 255);
    
    command = 'L';
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("left");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==1 && xSign==1){   // forwardright
    speed = 470-(1023-yValue);
    speed = map(speed, 0, 470, 0, 255);
    
    command = '1';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FR");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==1 && xSign==-1){   // forwardleft
    speed = 470-(1023-yValue);
    speed = map(speed, 0, 470, 0, 255);
    
    command = '2';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FL");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==-1 && xSign==1){   // backwardright
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);

    command = '4';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BR");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==-1 && xSign==-1){   // backwardleft
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);

    command = '3';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BL");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }
  else if(ySign==0 && xSign==0){   // stop
    speed = 0;
    
    command = 'S';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("stop");
    lcd.print(" ");
    lcd.print(speed);
    lcd.setCursor(0, 1);
    lcd.print("location: ");
    lcd.print(location);
    delay(100);
  }

  now = millis();  //RF통신 속도 
  if (now - 500 > lastSend) { 
    /* // 방향과 속도를 둘 다 보내기 위한 코드이나 송신 속도를 엄청 느리게해야 동시에 보낼 수 있기 때문에 일단 삭제
    speedSend = String(speed);
    sendString = command+","+speedSend; // should command to String
    sendString.toCharArray(send, 100);
    Serial.print("send:");
    Serial.write(send);
    Serial.println("");
    RFSerial.write(send);
    */
    RFSerial.write(command);
    lastSend = now;
  }
}
