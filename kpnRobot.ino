#include <ATX2.h>
///////////////////////////////
#define L analog(4)
#define R analog(5)
#define ref_L 525
#define ref_R 525
unsigned int PG = 0;
////////////////////////////////

void trackLine()
{

  if (L > ref_L && R > ref_R) {
    FD(40); //ตรง
  }
  if (L < ref_L && R > ref_R) {
    SL(50); //เลี้ยวซ้าย
  }
  if (L > ref_L && R < ref_R) {
    SR(50); //เลี้ยวขวา
  }
}

void pause(unsigned int time)
{
  AO();
  delay(time);
}

void TL90()
{
  SL(80);
  delay(100);
  while (L > ref_L) {
    SL(60);
  }
  while (L <= ref_L) {
    SL(60);
  }
  pause(200);
}

void TR90()
{
  SR(80);
  delay(100);
  while (R > ref_R) {
    SR(80);
  }
  while (R <= ref_R) {
    SR(80);
  }
  pause(200);
}

void FFF() //เจอแยกเดินตรง
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();

  ///// ปรับจนวิ่งผ่านแยกไป
  FD(20);
  delay(200);
}

void LLL() //เจอแยกเลี้ยวซ้าย
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();
  FD(40); delay(400); pause(1000);
  /////
  TL90();
}

void RRR() //เจอแยกเลี้ยวขวา
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();
  FD(40); delay(400); pause(1000);
  /////
  TL90();
}
//////////////////////////
//NOTE 
//servo-1 คีบ 70 กาง 100
//servo-2 วาง 0 ยก 80
void handSet()
{
  servo(1, 100); delay(300);
  servo(2, 80); delay(300);
}
void handDeploy()
{

  servo(2, 0); delay(300); //วาง
  servo(1, 100); delay(300); //กาง
  servo(2, 80); delay(300); //ยก
}

void handKeep()
{
  servo(1, 100); delay(1000); //กาง
  servo(2, 00); delay(1000); //วาง
  servo(1, 70); delay(1000); //คีบ
  servo(2, 80); delay(1000); //ยก
}
//////////////////////
void setServo(unsigned int chanel)
{
  unsigned int pos;
  pos = knob(180);
  glcd(2, 1, "SV %d: %d   ", chanel, pos);
  servo(chanel, pos);
}

void readSensor()
{
  glcd(3, 1, "L: %d   ", L);
  glcd(4, 1, "R: %d   ", R);
}
void setup() {
  XIO();
  OK();
}

void loop() {
readSensor();
}
