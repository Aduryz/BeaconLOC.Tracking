#include <LiquidCrystal_I2C.h>

char xPin = A0;
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

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){ 
  Serial.begin(9600);
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
    
  Serial.print(xValue,DEC);   // 시리얼 모니터에 값 표시
  Serial.print(",");
  Serial.print(yValue,DEC);
  Serial.print(",");
  Serial.print(!zValue);
  Serial.print("\n");
  Serial.print(carStance);
  Serial.print("\n");
  delay(50); 

  if(buttonValue==1){
    if(carStance==0){
      carStance = 1;
      delay(100);
    }
    else if(carStance==1){
      carStance = 0;
      delay(100);
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
    
    Serial.print("forward");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("forward");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==-1 && xSign==0){   // backward
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("backward");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("backward");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==0 && xSign==1){   // right
    speed = 470-(1023-xValue);
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("right");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("right");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==0 && xSign==-1){   // left
    speed = 470-xValue;
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("left");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("left");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==1 && xSign==1){   // forwardright
    speed = 470-(1023-yValue);
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("forwardright");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("forwardright");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==1 && xSign==-1){   // forwardleft
    speed = 470-(1023-yValue);
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("forwardleft");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("forwardleft");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==-1 && xSign==1){   // backwardright
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);
    Serial.print("backwardright");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("backwardright");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==-1 && xSign==-1){   // backwardleft
    speed = 470-yValue;
    speed = map(speed, 0, 470, 0, 255);
    
    Serial.print("backwardleft");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("backwardleft");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
  else if(ySign==0 && xSign==0){   // stop
    speed = 0;
    
    Serial.print("stop");
    Serial.print(",");
    Serial.print(speed);
    Serial.print("\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("stop");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    delay(100);
  }
}
