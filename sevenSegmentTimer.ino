int sevenSegTens[7]   = {7,8,9,10,11,12,13};
int sevenSegUnits[7]  = {0,1,2,A5,4,5,6};
int yellowLED         = A0;

bool segStateTens[7]  = {false, false, false, false, false, false, false};
bool segStateUnits[7] = {false, false, false, false, false, false, false};

bool startFlag = false;
bool interFlag = false;

int timer = 100;

void setup() {
  for(int i=0; i<7; i++){
    pinMode(sevenSegTens[i], OUTPUT);
    pinMode(sevenSegUnits[i], OUTPUT);
  }
  pinMode(yellowLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), halt5, RISING);
  
  dispState(sevenSegTens, segStateTens);
  dispState(sevenSegUnits, segStateUnits);
  digitalWrite(yellowLED, LOW);
  interrupts();
}

void loop() {
  if(startFlag){
    noInterrupts();
    delay(1000);
    interrupts();
    for(int i=99; i>=0; i--){
      timer = i;
      setState(segStateTens, (timer-(timer%10))/10);
      dispState(sevenSegTens, segStateTens);
      setState(segStateUnits, timer%10);
      dispState(sevenSegUnits, segStateUnits);
      delay(1000);
    }
    interFlag = false;
    startFlag = false;
//    gameover();
  }
}

void gameover(){
      while(0==0){
      setState(segStateTens, 0);
      dispState(sevenSegTens, segStateTens);
      setState(segStateUnits, 0);
      dispState(sevenSegUnits, segStateUnits);
    }
}

//Interrupt handler for Bomb Diffusal Project
void halt5(){
  if(!interFlag){
    interFlag = true;
    startFlag = true;
  }
  else{
    digitalWrite(yellowLED, HIGH);
    for(int i=0; i<5; i++){
      setState(segStateTens, -1);
      dispState(sevenSegTens, segStateTens);
      setState(segStateUnits, -1);
      dispState(sevenSegUnits, segStateUnits);
//      for(int j=0; j<25; j++)
//        delayMicroseconds(10000);
      setState(segStateTens, (timer-(timer%10))/10);
      dispState(sevenSegTens, segStateTens);
      setState(segStateUnits, timer%10);
      dispState(sevenSegUnits, segStateUnits);
//      for(int j=0; j<25; j++)
//        delayMicroseconds(10000);
    }
    digitalWrite(yellowLED, LOW);
  }
}

//Prints the values on 7-Segment Display according to the state array
void dispState(int sevenSegment[7], bool segmentState[7]){
  for(int i=0; i<7; i++){
    if(segmentState[i])
      digitalWrite(sevenSegment[i], HIGH);
    else
      digitalWrite(sevenSegment[i], LOW);
  }
}

//Sets the state array according to the value passed; value in (0,9) only
void setState(bool segmentState[], int value){
  switch (value){
    case 0:{
      bool newState[7] = {true, true, true, true, true, true, false};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 1:{
      bool newState[7] = {false, true, true, false, false, false, false};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 2:{
      bool newState[7] = {true, true, false, true, true, false, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 3:{
      bool newState[7] = {true, true, true, true, false, false, true};
      memcpy(segmentState, newState, 7);
      break;
      }
    case 4:{
      bool newState[7] = {false, true, true, false, false, true, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 5:{
      bool newState[7] = {true, false, true, true, false, true, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 6:{
      bool newState[7] = {true, false, true, true, true, true, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 7:{
      bool newState[7] = {true, true, true, false, false, false, false};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 8:{
      bool newState[7] = {true, true, true, true, true, true, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    case 9:{
      bool newState[7] = {true, true, true, false, false, true, true};
      memcpy(segmentState, newState, 7);
      break;
    }
    default:{
      bool newState[7] = {false, false, false, false, false, false, false};
      memcpy(segmentState, newState, 7);
      break;
    }
  }
}
