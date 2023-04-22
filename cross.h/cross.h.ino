#ifndef CROSS_H
#define CROSS_H

#include "straight_turn.h"

void cross(){
    if (checkState(&stage,&lastState) == 11111){//1 is black, 2 is white
    if(stage % 2 == 0){ // U turn 
      // UTurn(&stage, &lastState);
      // teststage ++ ;
      // Serial.println(teststage);
      UTurn(&stage, &lastState);
        // motorWriting(speed,-speed);   
        // Serial1.println("haha you are");   
      
    }

    else if(stage % 6 == 1){ // right turn
      // Serial1.println(stage);
      // Serial.println(stage);
      RightTurn(&stage, &lastState);
    }

    else if(stage%6 == 3){ // middle Node -> go straight
      while (checkState(&stage, &lastState) == 11111){//1 is black, 2 is white
        motorWriting(speed, speed);
      }
    }

    else if(stage%6 == 5){ // left turn
      LeftTurn(&stage, &lastState);
    }
  }
}

#endif