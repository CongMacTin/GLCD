// LCD5110_Scrolling_Text 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of how to use print().
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.

//
#include "LCD5110_Graph.h"
#define led 9
int volts = 0;
int Num[]={"0","1","2","3","4","5","6","7","8","9"};
int digitBuffer[5]={0};
LCD5110 myGLCD(7,6,5,3,4);

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

int y;

void setup()
{
  pinMode(led,HIGH);
  pinMode(A0,INPUT);
  analogWrite(led,120);
  myGLCD.InitLCD();
}
int check()
{
  int temp= analogRead(A0);
  volts=map(temp,0,1023,0,9999);
  return volts;
}
void convert()
{
  digitBuffer[4] = Num[int(volts)/1000];
  digitBuffer[3] = {"."};  
  digitBuffer[2] = Num[(int(volts)%1000)/100];
  digitBuffer[1] = Num[(int(volts)%100)/10];
  digitBuffer[0] = Num[(int(volts)%100)%10];
 // digitBuffer[3] = {"."};
}
void Display()
{
  myGLCD.setFont(SmallFont);
  myGLCD.print("Volts :", 0, 0);
  myGLCD.update();
  myGLCD.setFont(BigNumbers);
    for( int i=0;i<5;i++)
    {
      myGLCD.print(digitBuffer[i],70-(i*16), 18);
    }
  myGLCD.update();  
  delay(50);
}
void loop()
{
 check();
 convert();
 Display();
 
 }
