int morseLED = 13;
int pbs = 2; // submit button
int opt1 = 3; // switch 1
int opt2 = 4; // switch 2
int timer = 5; //pin for timer for the other arduino
int redLED = 12;
int resetTimer = 6;

int bit1 = 0; //switch 1 position
int bit2 = 0; // switch 2 position

float t[] = {12, 12.7, 12.9, 12}; // time needed for each morseCode to finish executing
float tmax = 12.9; // maximum time for a morseCode
int randModules[2];
int currentModule = 0;
int solved = 0;
int pauseCount = 0; // 2 pauses per module
int solvedFlag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(morseLED, OUTPUT);
  pinMode(pbs, INPUT);
  pinMode(opt1, INPUT);
  pinMode(opt2, INPUT);
  pinMode(timer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(resetTimer, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pbs), waitForUserSwitch, RISING);
  
  digitalWrite(resetTimer, LOW);
  delay(1);
  digitalWrite(resetTimer, HIGH);
  randomSeed(analogRead(0));
  //*********Main Code Starts Here*********//
  delay(1000);
  digitalWrite(timer, LOW);
  randomSelect2(randModules); //generate random index for random morse
  delay(1000);
  digitalWrite(timer, HIGH);
  delay(1);
  digitalWrite(timer, LOW);
  startMorse();
}

//initialize morse code with correct module
void startMorse(){
  solvedFlag = false;  
  while(solved != 2){ //there's still active modules
    if(solved == -1){ //a solve failed
      digitalWrite(morseLED, HIGH);
      digitalWrite(redLED, HIGH);
      Serial.println("BOOM");
      digitalWrite(resetTimer, LOW);
    }
    
//    delay((5+tmax-t[randModules[currentModule]])*1000);
    bombMorse(randModules[currentModule]);
    
  }

  //all modules are solved
  digitalWrite(redLED, LOW);
  digitalWrite(morseLED, LOW);
  Serial.println("Bomb Defused");
  while(0==0){
    digitalWrite(timer, HIGH);
    digitalWrite(timer, LOW);
  }
  
}

//check if module has been solved
void checkFlag(int sec){
  unsigned long initTime = millis();
  while(millis() - initTime < sec){
    if (solvedFlag == true){
      delay(1000);
      startMorse();
    }
  }
}

//interrupt function
void waitForUserSwitch(){
  noInterrupts();
  
  if(pauseCount >= 2){
    //no more pauses allowed
  }
  else{
    digitalWrite(timer, HIGH);
    pauseCount += 1;
    digitalWrite(timer, LOW);
    
    bit1 = digitalRead(opt1);
    bit2 = digitalRead(opt2);

    if(randModules[currentModule] == 0){
      if(bit1 == 0 && bit2 == 0){
        solved += 1;
        currentModule += 1;
        solvedFlag = true;
        Serial.println("Solved a module");
      }
      else{
        solved = -1;
      }
    }
    else if(randModules[currentModule] == 1){
      if(bit1 == 0 && bit2 == 1){
        solved += 1;
        currentModule += 1;
        solvedFlag = true;
        Serial.println("Solved a module");
      }
      else{
        solved = -1;
      }
    }
    else if(randModules[currentModule] == 2){
      if(bit1 == 1 && bit2 == 0){
        solved += 1;
        currentModule += 1;
        solvedFlag = true;
        Serial.println("Solved a module");
      }
      else{
        solved = -1;
      }
    }
    else if(randModules[currentModule] == 3){
      if(bit1 == 1 && bit2 == 1){
        solved += 1;
        currentModule += 1;
        solvedFlag = true;
        Serial.println("Solved a module");
      }
      else{
        solved = -1;
      }
    }
  }

  interrupts();
      
}

//generates array of randoom integers
int randomSelect2(int rand2[]){
  int firstSel = random(0,4);
  int secondSel = random(0,4);
  while (firstSel == secondSel){
    secondSel = random(0,4);
  }
  Serial.println(firstSel);
  Serial.println(secondSel);
  rand2[0] = firstSel;
  rand2[1] = secondSel;
  return rand2;
}

// code for different morse code words
void bombMorse(int index){
  if (index == 0){
    //SHELL
    for(int i = 0; i < 3; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);
    // H
    for(int i = 0; i < 4; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);
    // E
    digitalWrite(morseLED, HIGH);
    checkFlag(200);
    digitalWrite(morseLED, LOW);
    checkFlag(1000);
    // LL
    for(int i = 0; i < 2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(500);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(1000);
    }
  }

  else if (index == 1){
    //HALLS
    //H
    for(int i = 0; i < 4; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);
    //A
    digitalWrite(morseLED, HIGH);
    checkFlag(200);
    digitalWrite(morseLED, LOW);
    checkFlag(200);
    digitalWrite(morseLED, HIGH);
    checkFlag(500);
    digitalWrite(morseLED, LOW);
    checkFlag(1000);
    // LL
    for(int i = 0; i < 2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(500);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(1000);
    }
    // S
    for(int i = 0; i < 3; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);
  }

  else if (index == 2){
    // S
    for(int i = 0; i < 3; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);
    
    //L
    digitalWrite(morseLED, HIGH);
    checkFlag(200);
    digitalWrite(morseLED, LOW);
    checkFlag(200);
    digitalWrite(morseLED, HIGH);
    checkFlag(500);
    digitalWrite(morseLED, LOW);
    checkFlag(200);
    digitalWrite(morseLED, HIGH);
    checkFlag(200);
    digitalWrite(morseLED, LOW);
    checkFlag(200);
    digitalWrite(morseLED, HIGH);
    checkFlag(200);
    digitalWrite(morseLED, LOW);
    checkFlag(1000);

    //I
    for(int i = 0; i < 2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);

    //C
    for (int i =0; i <2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(500);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);

    //K
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(200);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     checkFlag(1000);
     
  }

  else if (index == 3){
    //T
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     checkFlag(1000);

     //R
     digitalWrite(morseLED, HIGH);
     checkFlag(200);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(200);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     checkFlag(1000);

     //I
     for(int i = 0; i < 2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
     }
     checkFlag(1000);

     //C
    for (int i =0; i <2; i++){
      digitalWrite(morseLED, HIGH);
      checkFlag(500);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
      digitalWrite(morseLED, HIGH);
      checkFlag(200);
      digitalWrite(morseLED, LOW);
      checkFlag(200);
    }
    checkFlag(1000);

    //K
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(200);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     digitalWrite(morseLED, HIGH);
     checkFlag(500);
     digitalWrite(morseLED, LOW);
     checkFlag(200);
     checkFlag(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:  

}
