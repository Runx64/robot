////////////////////////////////////////////////
///// Demo Robot 2021 By Narongsuk Sihawong ////
///// Kanchanapisekwittayalai Grup          ////
////////////////////////////////////////////////
#include <ATX2.h>
///////////////////////////////
#define L analog(4)
#define R analog(5)
#define ref_L 500
#define ref_R 500
unsigned int PG=0;
////////////////////////////////

void FD(unsigned int power,unsigned int time)
{
  FD(power); delay(time); 
}

void BK(unsigned int power,unsigned int time)
{
  BK(power); delay(time); 
}

void SL(unsigned int power,unsigned int time)
{
  SL(power); delay(time); 
}

void SR(unsigned int power,unsigned int time)
{
  SR(power); delay(time); 
}

void TL(unsigned int power,unsigned int time)
{
  TL(power); delay(time); 
}
void TR(unsigned int power,unsigned int time)
{
  TR(power); delay(time); 
}
void pause(unsigned int time)
{
 AO();
 delay(time);
}
///////////////////////////////////////////
void trackLine()
{
  
  if(L>ref_L && R>ref_R){FD(40);} //ตรง
  if(L<ref_L && R>ref_R){SL(50);} //เลี้ยวซ้าย
  if(L>ref_L && R<ref_R){SR(50);} //เลี้ยวขวา
}

void TL90()
{
 SL(60,100);
 while(L > ref_L){SL(60);}
 while(L <= ref_L){SL(60);}
 pause(200);
}

void TR90()
{
 SR(80,100);
 while(R > ref_R){SR(80);}
 while(R <= ref_R){SR(80);}
 pause(200);
}

void FFF()
{
 while(L>ref_L || R>ref_R){trackLine();} // แท็กเส้น จนกว่าเจอ "แยก"
 pause(100);
 beep();
 
 ///// ปรับจนวิ่งผ่านแยกไป
 FD(20,200);
}

void LLL()
{
 while(L>ref_L || R>ref_R){trackLine();} // แท็กเส้น จนกว่าเจอ "แยก"
 pause(100);
 beep();
 FD(40); delay(400); pause(1000);
 ///// 
 TL90();

}

void RRR()
{
 while(L>ref_L || R>ref_R){trackLine();} // แท็กเส้น จนกว่าเจอ "แยก"
 pause(100);
 beep();
 FD(40); delay(400); pause(1000);
 ///// 
 TL90();
}
//////////////////////////
void handSet()
{
  servo(1,110); delay(300);
  servo(2,110); delay(300);
}
void handUp()
{
  servo(1,110); delay(300);
  servo(2,110); delay(300);
}

void handDown()
{
  servo(1,110); delay(300);
  servo(2,110); delay(300);
}
//////////////////////
void setServo(unsigned int chanel)
{
  unsigned int pos;
  pos = knob(180);
  glcd(2,1,"SV %d: %d   ",chanel,pos);
  servo(chanel,pos);
}

void readSensor()
{
  glcd(3,1,"L: %d   ",L);
  glcd(4,1,"R: %d   ",R);
}
void setup() {
  XIO();
  glcdMode(3);
  setTextSize(2);
  setTextColor(GLCD_GREEN);
  glcd(2,1,"press OK!");
  sw_ok_press();
  setTextColor(GLCD_ORANGE);
  glcd(4,2,"Running..!");
  sound(2500,500);
  glcdClear();
    
  while(!sw_ok())
  {
    PG = knob(1,10);
    glcd(2,1,"Program: %d   ",PG);
  }
  sound(2500,500);
   
}

void loop() {

  //glcdClear();
  if(PG==1)
  {
    readSensor();
  }
  else if(PG==2)
  {
    setServo(1);
  }
  else if(PG==3)
  {
    trackLine();
  }
  else if(PG==4)
  {
    TL90(); pause(10000);
  }
  else if(PG==5)
  {
    TR90(); pause(10000);
  }
  else if(PG==6)
  {
    LLL(); pause(10000);
  }
  else if(PG==7)
  {
    RRR(); pause(10000);
  }
  else if(PG==8)
  {
    FFF(); pause(10000);
  }
  else if(PG==9)
  {
    
  }

}
