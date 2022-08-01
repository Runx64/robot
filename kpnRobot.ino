#include <ATX2.h>
///////////////////////////////
#define L analog(4)
#define R analog(5)
#define ref_L 592
#define ref_R 592
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
  pause(100);
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
  pause(100);
}

void FFF() //เจอแยกเดินตรง
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();

  ///// ปรับจนวิ่งผ่านแยกไป
  FD(50);
  delay(100);
}

void LLL() //เจอแยกเลี้ยวซ้าย
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();
  FD(50); delay(100);
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
  FD(50); delay(100);
  /////
  TR90();
}

void FFK() //เจอแยกคีบวัตถุ
{
  while (L > ref_L || R > ref_R) {
    trackLine(); // แท็กเส้น จนกว่าเจอ "แยก"
  }
  pause(100);
  beep();

  /////ถอยหลังจนได้ระยะ
  while(sonar()<9 || sonar()>30){
  BK(50);
  }
  pause(100);
  handKeep();
}

//////////////////////////
//servo-1 คีบ 65 กาง 100
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
  servo(1, 100); delay(300); //กาง
  servo(2, 00); delay(300); //วาง
  servo(1, 65); delay(300); //คีบ
  servo(2, 80); delay(300); //ยก
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
  glcd(5,1,"Sonar: %d    ",sonar());
}

///////////////////////////////
///////MAIN PROGRAM///////////
/////////////////////////////

void setup() {
  XIO();
  handSet();
  OK();

  FFF();
  RRR();
  FFF();
  FFF();
  FFK();
  pause(2000);
 
}

void loop() {
  //readSensor();
}
