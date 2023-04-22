#ifndef STRAIGHT_TURN_H
#define STRAIGHT_TURN_H

#define PWMA 11
#define AIN1 2
#define AIN2 3
#define BIN1 5
#define BIN2 6
#define PWMB 12

#define IR1 32
#define IR2 34
#define IR3 36
#define IR4 38
#define IR5 40

#define speed 255



void UTurn();
void RightTurn();
void LeftTurn();
void straight();
int checkState(int *, int *);
void motorWriting(int, int);

void UTurn(int *stage, int *lastState){
  motorWriting(speed, -speed);
  delay(620);
  motorWriting(speed,speed);
  delay(100);
  // motorWriting(speed, speed);
  // delay(150);
  // while (!(checkState(stage, lastState) == 22122)){
  //   motorWriting(speed, -speed);
  // }
}

void RightTurn(int *stage, int *lastState){
  motorWriting(speed, speed);
  delay(50);
  motorWriting(speed, 0);
  delay(650);
  // motorWriting(speed, speed);
  // delay(120);
}

void LeftTurn(int *stage, int *lastState){
  motorWriting(speed, speed);
  delay(50);
  motorWriting(0, speed);
  delay(650);
  // motorWriting(speed, speed);
  // delay(120);
}

void Forward(int *stage, int *lastState){
  while (checkState(stage, lastState) == 11111){//1 is black, 2 is white
    motorWriting(speed*7/8, speed);
  }
}

int checkState(int* stage, int* lastState){ //checking the states of IR, 1 means black, 2 means white
  if (digitalRead(IR1) == HIGH && digitalRead(IR2) == LOW && digitalRead(IR3) == LOW && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 12222;    
  }
  else if(digitalRead(IR1) == HIGH && digitalRead(IR2) == HIGH && digitalRead(IR3) == LOW && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 11222;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == HIGH && digitalRead(IR3) == LOW && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 21222;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == HIGH && digitalRead(IR3) == HIGH && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 21122;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == HIGH && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 22122;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == HIGH && digitalRead(IR4) == HIGH && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 22112;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == LOW && digitalRead(IR4) == HIGH && digitalRead(IR5) == LOW){
    *lastState = 2; // not all black
    return 22212;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == LOW && digitalRead(IR4) == HIGH && digitalRead(IR5) == HIGH){
    *lastState = 2; // not all black
    return 22211;
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == LOW && digitalRead(IR4) == LOW && digitalRead(IR5) == HIGH){
    *lastState = 2; // not all black
    return 22221;
  }
  else if(digitalRead(IR1) == HIGH && digitalRead(IR2) == HIGH && digitalRead(IR3) == HIGH && digitalRead(IR4) == HIGH && digitalRead(IR5) == HIGH){
    if (*lastState == 2){
      (*stage)++;
      (*lastState) = 1;
    }
    return 11111;
    
  }
  else if(digitalRead(IR1) == LOW && digitalRead(IR2) == LOW && digitalRead(IR3) == LOW && digitalRead(IR4) == LOW && digitalRead(IR5) == LOW){
    return 22222;
  }

}

void straight(int* stage, int* lastState){
  if(checkState(stage, lastState) == 12222){
    motorWriting(0,speed);
  }
  else if(checkState(stage, lastState) == 11222){
    motorWriting(0,speed);
  }
  else if(checkState(stage, lastState) == 21222){
    motorWriting(0,speed);
  }
  else if(checkState(stage, lastState) == 21122){
    motorWriting(0,speed);
  }
  else if(checkState(stage, lastState) == 22122){
    motorWriting(speed,speed);
  }
  else if(checkState(stage, lastState) == 22112){
    motorWriting(speed,0);
  }
  else if(checkState(stage, lastState) == 22212){
    motorWriting(speed,0);
  }
  else if(checkState(stage, lastState) == 22211){
    motorWriting(speed,0);
  }
  else if(checkState(stage, lastState) == 22221){
    motorWriting(speed,0);
  }
}

void motorWriting(int vL, int vR){
  if(vL > 0){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }else if (vL == 0){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);    
  }
  else{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }

  if(vR > 0){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }else if (vR == 0){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);    
  }
  else{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }

  analogWrite(PWMB, abs(vL));
  analogWrite(PWMA, abs(vR));
}


#endif