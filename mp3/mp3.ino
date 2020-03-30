#include "Pitches.h"
#include "Songs.h"
#define TIMETICK   500 // ms
#define TRUE    1
#define FALSE     0

const int btnPrevious = 2;
const int btnNext = 3;
const int segA = 4;
const int segB = 5;
const int segC = 6;
const int segD = 7;
const int segE = 8;
const int segF = 9;
const int segG = 10;
const int ledGreen = 11;
const int ledRed = 12;
const int potMeter = A0;
const int ldrMeter = A1;
const int speakerPin = A2;

// variables will change:
int potValue;
int ldrValue;
int btnStatePrevious = 0;         // variable for reading the pushbutton status
int lastStatePrevious = 0;
int btnStateNext = 0;             // variable for reading the pushbutton status
int lastStateNext = 0;
int songnumber = 0;               // variable for tracking which song is playing
int canPlayMusic = true;            // check if arduino can play music, dependent on the LDR sensor

unsigned long startTime = 0;
int currentNote = 0;
unsigned long currentMillis;
unsigned long difference;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Set button pins as INPUT
  pinMode(btnPrevious, INPUT);
  pinMode(btnNext, INPUT);

  // Set SEGMENT pins as OUTPUT
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  //digitalWrite(ledGreen,HIGH);
  //digitalWrite(ledRed, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  potValue = analogRead(potMeter) / 100;    // Value between 0 - 10, 10 being HIGH
  Serial.println(potValue);
  buttonState();
  ldrThings();
  
  playSong();

}

void buttonState() {
  btnStatePrevious = digitalRead(btnPrevious);
  btnStateNext     = digitalRead(btnNext);
  if(btnStatePrevious != lastStatePrevious) {
    if(btnStatePrevious == HIGH) {
      if(songnumber != 0) {
        songnumber--;
      }
    }
    lastStatePrevious = btnStatePrevious;
  }
  if(btnStateNext != lastStateNext) {
    if(btnStateNext == HIGH) {
      if(songnumber != 5) {
        songnumber++;
      }
    }
    lastStateNext = btnStateNext;
  }
}

void ldrThings() {
  ldrValue = analogRead(ldrMeter) / 100;    // Value between 0 - 10, 10 being bright
  Serial.println(ldrValue);
  if(ldrValue >= 3) {
    canPlayMusic = true;
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }
  else {
    canPlayMusic = false;
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    displayNone();
  }
}

void playSong() {
  if(canPlayMusic == true) {
    if(songnumber == 0){
      displayZero();
    }
    else if(songnumber == 1) {
      displayOne();
    }
    else if(songnumber == 2) {
      displayTwo();
    }
    else if(songnumber == 3) {
      displayThree();
    }
    else if(songnumber == 4) {
      displayFour();
    }
    else {
      displayFive();
      for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {
        int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
        int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
        tone(speakerPin, Pirates_note[thisNote], noteDuration);
        //delay(pauseBetweenNotes);
        noTone(speakerPin);
      }
      for(int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {
        
      }
    }
  }
  else {
    displayNone();
  }
}

void changeNote(int noteSize) {
  startTime = millis();
  if(currentNote >= noteSize) {
    currentNote = 0;
  }
  else {
    currentNote++;
  }
  noTone(speakerPin);
}

void displayNone() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void displayZero() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
}
void displayOne() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void displayTwo() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}
void displayThree() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}
void displayFour() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void displayFive() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
