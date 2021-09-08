// 비콘을 이용한 자율주행 배달 시스템 - 자동차

int rMoterS = 10;   // Moter Speed
int lMoterS = 11;    
int rMoterD = 12;   // Moter Direction, HIGH가 직진
int lMoterD = 13;   // LOW가 직진
int speed = 255;

int trigPin = 9;    // 초음파 센서
int echoPin = 8;
float obstacle = 10;    // [cm]

char command;   // 블루투스로부터 수신

int stance = 0;   // 상태를 나타내는 변수
int led = 7;

void setup(){               // 핀모드 설정 & 시리얼 통신 시작
  Serial.begin(9600);
  
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
    analogWrite(rMoterS,100);
    analogWrite(lMoterS,100);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,LOW);
    delay(100);
    analogWrite(rMoterS,0);
    analogWrite(lMoterS,0);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,LOW);
    break;
  }
    
  if(Serial.available() > 0){   // 블루투스 조작
    command = Serial.read(); 
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
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,LOW);
}

void left(){    // 좌회전 (좌측후진, 우측전진)
    analogWrite(rMoterS,speed);
    analogWrite(lMoterS,speed);
    digitalWrite(rMoterD,HIGH);
    digitalWrite(lMoterD,HIGH);
}

void forwardright(){     // forwardright
    analogWrite(rMoterS,speed/2);
    analogWrite(lMoterS,speed);
    digitalWrite(rMoterD,HIGH);
    digitalWrite(lMoterD,LOW);
}

void forwardleft(){     // forwardleft
    analogWrite(rMoterS,speed);
    analogWrite(lMoterS,speed/2);
    digitalWrite(rMoterD,HIGH);
    digitalWrite(lMoterD,LOW);
}

void backwardright(){    // backwardright
    analogWrite(rMoterS,speed/2);
    analogWrite(lMoterS,speed);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,HIGH);
}

void backwardleft(){    // backwardleft
    analogWrite(rMoterS,speed);
    analogWrite(lMoterS,speed/2);
    digitalWrite(rMoterD,LOW);
    digitalWrite(lMoterD,HIGH);
}

void stop(){    // 정지
    analogWrite(rMoterS,0);
    analogWrite(lMoterS,0);
}
