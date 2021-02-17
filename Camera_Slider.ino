/*
DIY Arduino Camera Slider
 Brandon Tsuge

This is the code that I used to control two stepper motors for a DIY camera phone slider with sliding and panning motion 
https://www.theboredrobot.com/post/diy-arduino-camera-phone-slider
 
 */



//Declare pin functions on the EasyDriver
#define Slide_stp 2 //Logic input: transition from LOW to HIGH to move one step
#define Slide_dir 3 //Direction
#define Slide_MS1 4 //MS1 and MS2 are logic pins from step size
#define Slide_MS2 5 //https://learn.sparkfun.com/tutorials/easy-driver-hook-up-guide?_ga=2.13257203.554998849.1612426132-1952729559.1604906281 for truth table
#define Slide_EN  6 //Enable

#define Pan_stp 7
#define Pan_dir 8
#define Pan_MS1 9
#define Pan_MS2 10
#define Pan_EN  11

#define Button1 12 //pin for limit switches

//counters
unsigned long previousSlide = millis();
unsigned long previousPan = millis();
long slideInterval = 1;
long panInterval = 75;

//define direction state
bool SlideDirVal = HIGH;
bool PanDirVal = LOW;

void setup() {
  //define EasyDriver Pins on Arduino
  pinMode(Slide_stp, OUTPUT);
  pinMode(Slide_dir, OUTPUT);
  pinMode(Slide_MS1, OUTPUT);
  pinMode(Slide_MS2, OUTPUT);
  pinMode(Slide_EN, OUTPUT);

  pinMode(Pan_stp, OUTPUT);
  pinMode(Pan_dir, OUTPUT);
  pinMode(Pan_MS1, OUTPUT);
  pinMode(Pan_MS2, OUTPUT);
  pinMode(Pan_EN, OUTPUT);

  //define button
  pinMode(Button1, INPUT);
  
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
}

//Main loop
void loop() {
  unsigned long currentSlide = millis();
  unsigned long currentPan = millis();
  
  digitalWrite(Slide_EN, LOW);
  digitalWrite(Slide_dir, SlideDirVal);
  digitalWrite(Slide_MS1, LOW);
  digitalWrite(Slide_MS2, LOW);
  digitalWrite(Slide_stp, LOW);

  digitalWrite(Pan_EN, LOW);
  digitalWrite(Pan_dir, PanDirVal);
  digitalWrite(Pan_MS1, HIGH);
  digitalWrite(Pan_MS2, HIGH);
  digitalWrite(Pan_stp, LOW);

//Check if the limit switch is pressed. If so, change the sliding motor direction
  if (digitalRead(Button1) == HIGH && SlideDirVal == HIGH){
    SlideDirVal = LOW;
    digitalWrite(Slide_dir, SlideDirVal);
    while (digitalRead(Button1) == HIGH){
      digitalWrite(Slide_stp, HIGH);
      digitalWrite(Slide_stp, LOW);
      delay(10);
      }
    }

  if (digitalRead(Button1) == HIGH && SlideDirVal == LOW){
    SlideDirVal = HIGH;
    digitalWrite(Slide_dir, SlideDirVal);
    while (digitalRead(Button1) == HIGH){
      digitalWrite(Slide_stp, HIGH);
      digitalWrite(Slide_stp, LOW);
      delay(10);
      }
    }

//run the motors are the defined time intervals.
  if(currentSlide - previousSlide > slideInterval){
    digitalWrite(Slide_stp, HIGH);
    previousSlide = currentSlide;
  }
  else if(currentPan - previousPan > panInterval){
    digitalWrite(Pan_stp, HIGH);
    previousPan = currentPan;
  }



}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(Slide_stp, LOW);
  digitalWrite(Slide_dir, LOW);
  digitalWrite(Slide_MS1, LOW);
  digitalWrite(Slide_MS2, LOW);
  digitalWrite(Slide_EN, HIGH);

  digitalWrite(Pan_stp, LOW);
  digitalWrite(Pan_dir, LOW);
  digitalWrite(Pan_MS1, LOW);
  digitalWrite(Pan_MS2, LOW);
  digitalWrite(Pan_EN, HIGH);
}
