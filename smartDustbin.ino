#include <Servo.h>
#include <NewPing.h>
#include <TimedAction.h>
#include <HC7Segment.h>

Servo servo;

int trigPin = A0;
int echoPin = A1;
int trigPin1 = A2;
int echoPin1 = A3;
long duration;
int distance;
long duration1;
int distance1;
int index;

int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = 6;
int segF = 7;
int segG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

int procent;

int distInProc(int dist)
{
  float proc = (dist * 100) / 28; //28-inaltimea pubelei
  return proc;
}

#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define DISPLAY_BRIGHTNESS 5000
boolean sem1 = false;
boolean sem2 = false;

void setup() {
  // put your setup code here, to run once:
  servo.attach(A4);
  servo.write(0);
  delay(2000);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int aux = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print("DistanceInt: ");
  Serial.println(distance1);

  procent = distInProc(distance1);
  Serial.println(procent);

  int figur1 = 100 - procent;
  int figur = figur1;
  if (figur1 > 67)
    figur = 100;

  if (distance <= 30)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    aux = 1;
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (figur != 100 and aux == 1)
  {
    servo.write(0);
    delay(3000);

  }
  else
  {
    servo.write(90);
  }

  lightNumber(10);
  
  digitalWrite(D1, DIGIT_OFF);
  digitalWrite(D2, DIGIT_OFF);
  digitalWrite(D3, DIGIT_OFF);
  digitalWrite(D4, DIGIT_OFF);

  figur1 = 100 - procent;
  figur = figur1;
  if (figur1 > 67)
    figur = 100;

  sem1 = false;
  sem2 = false;
  if (figur >= 0 && figur <= 100) {
    for (int digit = 1 ; digit < 5 ; digit++) {

      switch (digit) {
        case 1:
          if (figur > 999) {
            digitalWrite(D1, DIGIT_ON);
            lightNumber(figur / 1000);
            figur %= 1000;

            delayMicroseconds(DISPLAY_BRIGHTNESS);
            if (figur < 100) {
              sem1 = true;
              if (figur < 10) {
                sem2 = true;

              }

            } else sem1 = false;
          }

          break;
        case 2:
          if (sem1 == true) {
            digitalWrite(D2, DIGIT_ON);
            lightNumber(0);
            delayMicroseconds(DISPLAY_BRIGHTNESS);

          } if (sem2 == true) {
            break;
          }

          if (figur > 99 && figur < 1000) {
            digitalWrite(D2, DIGIT_ON);
            lightNumber(figur / 100);
            figur %= 100;
            delayMicroseconds(DISPLAY_BRIGHTNESS);
            if (figur < 10) {
              sem2 = true;

            } else sem2 = false;
          }
          break;
        case 3:
          if (sem2 == true) {
            digitalWrite(D3, DIGIT_ON);
            lightNumber(0);
            delayMicroseconds(DISPLAY_BRIGHTNESS);
            break;
          }

          if (figur > 9 && figur < 100) {
            digitalWrite(D3, DIGIT_ON);
            lightNumber(figur / 10);
            figur %= 10;
            delayMicroseconds(DISPLAY_BRIGHTNESS);
          }

          break;
        case 4:
          if (figur < 10) {
            digitalWrite(D4, DIGIT_ON);
            lightNumber(figur);
            delayMicroseconds(DISPLAY_BRIGHTNESS);

            break;
          }
      }

      lightNumber(10);

      digitalWrite(D1, DIGIT_OFF);
      digitalWrite(D2, DIGIT_OFF);
      digitalWrite(D3, DIGIT_OFF);
      digitalWrite(D4, DIGIT_OFF);

    }
  }
}

void lightNumber(int numberToDisplay) {
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW
  switch (numberToDisplay) {
    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
  }
}
