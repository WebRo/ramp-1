
//*******************************//
//------Bayram Ramp's code ------//
//*******************************//

int OutPins[] = {
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12
};

int InPins[] = {
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31
};

int pinCount = 10; // Array counter

int motorSpeedPin = 4; // Analog Pin for Motor Speed

int motorAcc = 80; // Motor speed acceleration.

int motorDirPin = 3; // Direction Pin for DC Door Motor

int stepsDelay = 4000; //Time between the steps

//-----------Relays Pins---------//
int DoorRelay = 5; // Door Relay Pin

int BigRampRelayMotor_Open = 7;//

int BigRampRelayMotor_Close = 6;//

int SmallRampRelayMotor_Open = 9; //

int SmallRampRelayMotor_Close = 8; //
//----------------- READING STATS AND VAL PINS-------
  int stateOpenDoor; // Open End the Door
  int stateCloseDoor; // Cloes End the Door
  int stateButtonA; // OPEN THE DOOR BTN
  int stateButtonB; // CLOSE THE DOOR BTN
  int stateButtonC; // emergency stop button
  int stateButtonD; // D PIN NOT USES FOR NOW IN THE REMOTE CONTROL
  int stateOpenBigRamp; // Open big Ramp 220 V.
  int stateCloseBigRamp; // Close Big Ramp 220 V.
  int stateOpenSmallRamp; // Open small ramp
  int stateCloseSmallRamp; // Open small ramp

//-------------BOOLEAN VALUES---------------//

bool opening;//
bool closing;//
bool OpenTheDoor; //
bool CloseTheDoor; ////////////  CONTROLING THE DOOR AND RAMPS STEPS
bool OpenTheBigRamp; ///////
bool CloseTheBigRamp; //
bool OpenTheSmallRamp; ///
bool CloseTheSmallRamp; //
bool CloseTheArm; //

void setAllRelaysOff() {
  //--------------SET ALL RELAYS OFF ----------------------//
  analogWrite(motorSpeedPin, 0); // SET the DC motor driver off
  digitalWrite(DoorRelay, HIGH); //  Set the Door Relay off
  digitalWrite(BigRampRelayMotor_Open, HIGH); //  Set the BigRampRelayMotor_Open off
  digitalWrite(BigRampRelayMotor_Close, HIGH); //  Set the BigRampRelayMotor_Close off
  digitalWrite(SmallRampRelayMotor_Open, HIGH); //  Set the SmallRampRelayMotor_Open  off
  digitalWrite(SmallRampRelayMotor_Close, HIGH); //  Set the SmallRampRelayMotor_Close off
  opening = false;
  closing =false;
  OpenTheDoor = true;
  CloseTheDoor = false;
  OpenTheBigRamp = false;
  CloseTheBigRamp = false;
  OpenTheSmallRamp = false;
  CloseTheSmallRamp = false;
  CloseTheArm = false;
  //Serial.println("Emergency Stop");
}





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(InPins[thisPin], INPUT);
  };

  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(OutPins[thisPin], OUTPUT);
  };

  setAllRelaysOff();// Starter function. With  all relays off and the steps controller
}

void loop() {
  //----------------- READING THE BUTTOMS AND (ON/OFF)SWITCHS-----------------//

  int stateOpenDoor = digitalRead(23); // Open End the Door
  int stateCloseDoor = digitalRead(22); // Cloes End the Door
  int stateButtonA = digitalRead(27); // OPEN THE DOOR BTN
  int stateButtonB = digitalRead(25); // CLOSE THE DOOR BTN
  int stateButtonC = digitalRead(26); // emergency stop button
  int stateButtonD = digitalRead(24); // D PIN NOT USES FOR NOW IN THE REMOTE CONTROL
  int stateOpenBigRamp = digitalRead(29); // Open big Ramp 220 V.
  int stateCloseBigRamp = digitalRead(28); // Close Big Ramp 220 V.
  int stateOpenSmallRamp = digitalRead(31); // Open small ramp
  int stateCloseSmallRamp = digitalRead(30); // Open small ramp

//-------------- cheking states---------------
if(stateButtonA==1){
  
    opening = true;
    closing = false;
  }
if(stateButtonB==1){
    opening = false;
    closing = true;
  }  
//Serial.println(stateOpenDoor);

  //-------------------WHEN BTN A ACTIVE OPINING OPERATION STARTS----------------//
  if(opening == true){
     if (OpenTheDoor == true) {
    //--------- 1:OPEN THE DOOR----------//
    if (stateOpenDoor == HIGH) {
      digitalWrite(DoorRelay, LOW);
      digitalWrite(motorDirPin, HIGH); // HIGH TO OPEN, LOW TO CLOSE THE MOTOR ARM
   // analogWrite(motorSpeedPin, motorAcc);
    //delay(1000);
      while (motorAcc <= 255) {
        analogWrite(motorSpeedPin, motorAcc);
       Serial.println(motorAcc);
        motorAcc++;
        delay(35);
        
      }
      //analogWrite(motorSpeedPin, 255);
      Serial.println("OPening");
    } else if (stateOpenDoor == LOW) {
      analogWrite(motorSpeedPin, 0);
      digitalWrite(DoorRelay, HIGH);
      motorAcc = 80;
      Serial.println("Stop-----------");
      delay(stepsDelay);
      OpenTheBigRamp = true;
      OpenTheDoor = false;
    }
  }

  //---- 2: OPEN THE BIG RAMP ----//

  if (OpenTheBigRamp == true) {

    if (stateOpenBigRamp == HIGH) {
      digitalWrite(BigRampRelayMotor_Open, LOW); //  Set the BigRampRelayMotor_Open on
    } else if (stateOpenBigRamp == LOW) {
      digitalWrite(BigRampRelayMotor_Open, HIGH); //  Set the BigRampRelayMotor_Open off
      delay(stepsDelay);
      OpenTheSmallRamp = true;
      OpenTheBigRamp = false;
    }
  }

  //------- 3: OPEN THE SMALL RAMP -----
  if (OpenTheSmallRamp == true) {
    if (stateOpenSmallRamp == HIGH) {
      digitalWrite(SmallRampRelayMotor_Open, LOW); //  Set the SmallRampRelayMotor_Open  on
    } else if (stateOpenSmallRamp == LOW) {
      digitalWrite(SmallRampRelayMotor_Open, HIGH); //  Set the BigRampRelayMotor_Open off
      delay(stepsDelay);
      CloseTheSmallRamp = true;
      OpenTheSmallRamp = false;
    }
  }

    }// END OF OPINGING

    
  //-------------------WHEN BTN B ACTIVE, CLODE OPERATIONS STARTS----------------//
  if(closing== true){
      //-------  1: CLOSE THE SMALL RAMP -------------
  if (CloseTheSmallRamp == true) {
    if (stateCloseSmallRamp == HIGH) {
      digitalWrite(SmallRampRelayMotor_Close, LOW); //  Set the SmallRampRelayMotor_Close on
    } else if (stateCloseSmallRamp == LOW) {
      digitalWrite(SmallRampRelayMotor_Close, HIGH); //  Set the SmallRampRelayMotor_Close off
      delay(stepsDelay);
      CloseTheBigRamp = true;
      CloseTheSmallRamp = false;
    }
  }
  //---------2: CLOSING THE BIG RAMP ---------------
  if (CloseTheBigRamp == true) {
    if (stateCloseBigRamp == HIGH) {
      digitalWrite(BigRampRelayMotor_Close, LOW); //  Set the BigRampRelayMotor_Close on
    } else if (stateCloseBigRamp == LOW) {
      digitalWrite(BigRampRelayMotor_Close, HIGH); //  Set the BigRampRelayMotor_Close off
      delay(stepsDelay);
      CloseTheDoor = true;
      CloseTheBigRamp = false;
    }
  }
  //------------ 3: CLOISING THE ARM OF THE DOOR
  if (CloseTheDoor == true) {
    if (stateCloseDoor == HIGH) {
      digitalWrite(motorDirPin, LOW); // HIGH TO OPEN, LOW TO CLOSE THE MOTOR ARM
      analogWrite(motorSpeedPin, 100);
    } else if (stateCloseDoor == LOW) {
      analogWrite(motorSpeedPin, 0);
      setAllRelaysOff();
    }
  }

    }// END OF CLOSING  
 
  if (stateButtonC == 1) {
    //  setAllRelaysOff();
    // CloseTheSmallRamp = true;//I set it true in case the user wants to close the system after the emergency stop.
  }

  //---------------------TEST CODE-------------------------//

  //-------------------------------------------------------//
}
