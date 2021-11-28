// Beacon을 이용한 위치추적과 자율주행 자동차 - 자동차
#include <SoftwareSerial.h>
SoftwareSerial RFSerial(2, 3); //TX to 2, RX to 3
SoftwareSerial BSerial(5, 6); //TX to 5, RX to 6

int rMoterS = 10;   // Moter Speed
int lMoterS = 11;    
int rMoterD = 12;   // Moter Direction, HIGH가 직진
int lMoterD = 13;   // LOW가 직진
int speed = 255;

int trigPin = 9;    // 초음파 센서
int echoPin = 8;
float obstacle = 10;    // [cm]

String receive; // RF통신
int receiveLength;
String commandReceive;
String speedReceive;
int comma;
char command;

int stance = 1;   // 상태를 나타내는 변수
int led = 7;

String val; //Beacon receive
char location;
long lastSend, now;

String pink;
String pinkR; //RSSI
int pR;
int headP;  //parsing
int tailP;
int headPR;
int tailPR;
int pinkP = 0;
String orange;
String orangeR;
int oR;
int headO;
int tailO;
int headOR;
int tailOR;
int orangeP = 0;
String yellow;
String yellowR;
int yR;
int headY;
int tailY;
int headYR;
int tailYR;
int yellowP = 0;

void setup(){               // 핀모드 설정 & 시리얼 통신 시작
  Serial.begin(9600);
  RFSerial.begin(9600);
  BSerial.begin(9600);
  
  pinMode(rMoterS,OUTPUT);
  pinMode(lMoterS,OUTPUT);
  pinMode(rMoterD,OUTPUT);
  pinMode(lMoterD,OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led,OUTPUT);
}

void loop(){
  float duration, distance;      // 초음파 거리 측정
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance = duration * 17 / 1000;    // distance={(34000*duration)/1000000}/2 (cm)

  while(!(distance >= obstacle) && stance==1){   // 장애물 감지 & 회피 (우회전)
    analogWrite(rMoterS,150);
    analogWrite(lMoterS,150);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,LOW);
    delay(500);
    analogWrite(rMoterS,0);
    analogWrite(lMoterS,0);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,LOW);
    break;
  }

  if(RFSerial.available()){   // RF통신 조작
    /* 방향과 속도를 둘 다 받기 위한 코드 이나 송신 속도를 엄청 느리게해야 동시에 보낼 수 있기 때문에 일단 비활성화
    receive = RFSerial.read();
    receiveLength = receive.length();
    comma = receive.indexOf(",");
    commandReceive = receive.substring(0, comma);
    speedReceive = receive.substring(comma, receiveLength);
    commandReceive.toCharArray(command, 100);
    speed = speedReceive.toInt(); 
    Serial.write(command);
    Serial.write(speed);
    */
    command = RFSerial.read();  // RF수신
    //Serial.write(RFSerial.read());
    //Serial.write(command);
    //Serial.println(" ");
    
    stop();
    switch(command){
      case 'Y':
        stance = 1;
        break;
      case 'N':
        stance = 0;
        break;          
      if(stance==1){
        case 'B':  
          backward();
          break;
        case 'A':
          scan();
          break;
        if(distance > obstacle){ 
          case 'F':  
            forward();
            break;
          case 'R':  
            right();
            break;
          case 'L':
            left();
            break;
          case '1':  
            forwardright();
            break;
          case '2':  
            forwardleft();
            break;
          case '4':
            backwardright();
            break;
          case '3':
            backwardleft();
            break;
          case 'S':
            stop();
            break;
        }
      }
    }
  }

  if(stance==1){                  // on
    digitalWrite(led, HIGH);
  }
  
  if(stance==0){                  // off
    analogWrite(rMoterS,0);
    analogWrite(lMoterS,0);
    digitalWrite(led, LOW);
  }

  if (BSerial.available()){
    String val = BSerial.readString();
    Serial.print("I received: ");
    Serial.println(val);  //beacon scan value
    delay(500);

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

      //Serial.print("pinkR: ");
      //Serial.println(pinkR);
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

      //Serial.print("orangeR: ");
      //Serial.println(orangeR);
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

      //Serial.print("yellowR: ");
      //Serial.println(yellowR);
      if (yellow=="74:F0:7D:1A:02:E8"){
        yellowP = 1;
      }
    }

    pR = pinkR.toInt();
    oR = orangeR.toInt();
    yR = yellowR.toInt();
    if(pR>-90 && oR<-90 && yR<-90){
      location = 'A';
    }
    else if(pR<-90 && oR>-90 && yR<-90){
      location = 'B';
    }
    else if(pR<-90 && oR<-90 && yR>-90){
      location = 'C';
    }
    else if(pR>-90 && oR>-90 && yR<-90){
      location = 'D';
    }
    else if(pR>-90 && oR<-90 && yR>-90){
      location = 'E';
    }
    else if(pR<-90 && oR>-90 && yR>-90){
      location = 'F';
    }
    else if(pR>-90 && oR>-90 && yR>-90){
      location = 'G';
    }
    else{
      location = 'U';
    }

    now = millis();
    if (now - 500 > lastSend) { 
      RFSerial.write(location);
      lastSend = now;
    }
  }
}

void forward(){     // 전진
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,HIGH);
  digitalWrite(lMoterD,LOW);
}

void backward(){    // 후진
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,LOW);
  digitalWrite(lMoterD,HIGH);
}

void right(){   // 우회전 (좌측전진, 우측후진)
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,HIGH);
  digitalWrite(lMoterD,HIGH);
}

void left(){    // 좌회전 (좌측후진, 우측전진)
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,LOW);
  digitalWrite(lMoterD,LOW);
}

void forwardright(){     // forwardright
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed/4);
  digitalWrite(rMoterD,HIGH);
  digitalWrite(lMoterD,LOW);
}

void forwardleft(){     // forwardleft
  analogWrite(rMoterS,speed/4);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,HIGH);
  digitalWrite(lMoterD,LOW);
}

void backwardright(){    // backwardright
  analogWrite(rMoterS,speed);
  analogWrite(lMoterS,speed/4);
  digitalWrite(rMoterD,LOW);
  digitalWrite(lMoterD,HIGH);
}

void backwardleft(){    // backwardleft
  analogWrite(rMoterS,speed/4);
  analogWrite(lMoterS,speed);
  digitalWrite(rMoterD,LOW);
  digitalWrite(lMoterD,HIGH);
}

void stop(){    // 정지
  analogWrite(rMoterS,0);
  analogWrite(lMoterS,0);
}

void scan(){
  pinkP = 0;
  orangeP = 0;
  yellowP = 0;
  delay(1000);  // 꼭 있어야함
  BSerial.println("AT+SCAN"); //beacon scan
}
