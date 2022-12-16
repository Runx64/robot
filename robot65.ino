#include <ATX2.h>  // ATX2 Board
//กำหนดตัวแปรเซ็นเซอร์วัดแสงสะท้อน
#define ll analog(1)  //ซ้ายสุด
#define lc analog(2)  //ซ้ายกลาง
#define rc analog(3)  //ขวากลาง
#define rr analog(4)  //ขวาสุด
#define bl analog(5)  //หลังซ้าย
#define br analog(6)  //หลังขวา
#define ref 600   //กำหนดค่ากลางค่าแสง
#define ref2 550

void readsensor(){  //ฟังก์ชันแสดงค่าจาก sensor 6 ตัว
glcd(0,0,"%d   ",ll);
glcd(0,5,"%d   ",lc);
glcd(0,10,"%d   ",rc);
glcd(0,15,"%d   ",rr);
glcd(3,0,"%d   ",bl);
glcd(3,10,"%d   ",br);
}

void pause(unsigned int time){  //ฟังก์ชันหยุดหุ่น
  ao();
  delay(time);
}

void Fset_balance(){   //ชนหน้าแล้ว set หน้าให้ตรง
if(ll < ref && rr > ref){
      while (rr > ref) {
    motor(1,0);        
    motor(2,50);  //ซ้ายเจอดำให้เลี้ยวขวาจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(100);
}
if(ll > ref && rr < ref){
    while (ll > ref) {
    motor(1,50);        
    motor(2,0);  //ขวาเจอดำให้เลี้ยวซ้ายจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(100);
}}

void Bset_balance(){    //ชนหลังแล้ว set หลังให้ตรง
if(bl < ref2 && br > ref2){
      while (br > ref2) {
    motor(1,0);    
    motor(2,-50); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(100);
}
if(bl > ref2 && br < ref2){
    while (bl > ref2) {
    motor(1,-50);        
    motor(2,0); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(100);
}}

void FF(){  //เดินหน้าและ check ซ้ายขวาไม่ให้ชนขอบด้านข้าง
  fd(60);
  if (ll<ref){  //ซ้ายเจอดำให้หมุนขวา
    sr(50);}
  if(rr<ref){   //ขวาเจอดำให้หมุนซ้าย
    sl(50);}
}

void FFBKL(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวซ้าย
  while(lc > ref && rc > ref){
  FF();
}
if(lc<ref || rc<ref){
  pause(100);
  Fset_balance();
}
if(lc < ref && rc < ref){
  pause(500);
}
bk(50); //ถอยหลังแล้วหมุน
delay(300);
sr(50);
delay(260);
while(bl > ref2 && br > ref2){  //ถอยจนกว่าจะชน
  bk(40);
}
if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
  pause(100);
  Bset_balance();
}
if(bl < ref2 && br < ref2){
  pause(500);
}}

void FFBKR(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวขวา
  while(lc > ref && rc > ref){
  FF();
}
if(lc<ref || rc<ref){
  pause(100);
  Fset_balance();
}
if(lc < ref && rc < ref){
  pause(500);
}
bk(50); //ถอยหลังแล้วหมุน
delay(300);
sl(50);
delay(260);
while(bl > ref2 && br > ref2){  //ถอยจนกว่าจะชน
  bk(40);
}
if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
  pause(100);
  Bset_balance();
}
if(bl < ref2 && br < ref2){
  pause(500);
}}

void setup() {  //โปรแกรมหลัก
  XIO(); // ATX2 initialize
  OK();  //ให้รอกด ok ค่อยไป
  delay(1000);
  beep(500);
  FFBKL();  FFBKL();  FFBKL();
  FFBKR();  FFBKR();  FFBKR();
  FF(); delay(1000); beep(500); pause(500);
  sr(50); delay(260);
  FF(); delay(1000); beep(500); pause(500);
}

void loop() {
    //readsensor();
}
