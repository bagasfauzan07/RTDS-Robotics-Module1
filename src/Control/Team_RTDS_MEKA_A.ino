/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1 //Dynamixel on Serial1(USART1) <-OpenCM9.04
#define DXL_BUS_SERIAL2 2 //Dynamixel on Serial2(USART2) <-LN101,BT210
#define DXL_BUS_SERIAL3 3 //Dynamixel on Serial3(USART3) <-OpenCM 485EXP

#include <Servo.h>
Servo myservo;

/* Dynamixel ID defines */
#define ID_NUM2 2
#define ID_NUM1 1
/* Control table defines */
#define GOAL_POSITIONL 30
#define GOAL_POSITIONH 31
#define PRESENT_POS 36
#include<math.h>
int min_pos = 215; //0 degree
int mid_pos = 512; //90 degree
int max_pos = 805; //180 degree
int a=0;
int b=1023;
float i;
boolean flag=0;
int pos1, pos2;
float l2 = 6.4;
float l1 = 6.7;
int input1, input2, rawdata1, rawdata2, inputT1, inputT2;
float T1, T2, T1rad, T2rad, X, Y, c, d, e, f, g, T2deg, T1deg;
Dynamixel Dxl(DXL_BUS_SERIAL3);



void setup() {
  myservo.attach(2);
  myservo.write(0);  
  
 // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps
 Dxl.begin(3);
 Dxl.jointMode(ID_NUM1); //lengan 1 joint mode
 Dxl.jointMode(ID_NUM2); //lengan 2 joint mode
}
void gerak() {
 c = (X*X)+(Y*Y)-(l1*l1)-(l2*l2);
 d = 2*l1*l2;
 e = c/d;
 T2rad = acos(e);
 T2deg = (T2rad*180)/3.141592654;
 f = atan2(Y,X);
 g = atan2((l2*sin(T2rad)),(l1+l2*cos(T2rad)));
 T1rad = f-g;
 T1deg = (T1rad*180)/3.141592654;
 input1 = T1deg;
 input2 = T2deg;
 inputT1 = ((input1*614)/180)+205;
 inputT2 = (((input2+90)*614)/180)+205;
 Dxl.writeWord(ID_NUM1, GOAL_POSITIONL, inputT1); //Compatible with all dynamixel serise
 Dxl.writeWord(ID_NUM2, GOAL_POSITIONL, inputT2); //Compatible with all dynamixel serise
 pos1 = Dxl.readWord(ID_NUM1, PRESENT_POS);
 if (pos1>=1023){
 pos1=input1;
 }
 pos2 = Dxl.readWord(ID_NUM2, PRESENT_POS);
 if (pos2>=1023){
 pos2=input2;
 }
 SerialUSB.print(X); SerialUSB.print("\t");
 SerialUSB.print(Y); SerialUSB.print("\t");
 SerialUSB.print(input1); SerialUSB.print("\t");
 SerialUSB.print(input2); SerialUSB.print("\t");
 SerialUSB.print(pos1); SerialUSB.print("\t");
 SerialUSB.print(pos2); SerialUSB.print("\t");
 SerialUSB.print("\n");
 delay(50);
}

void setengahlingkaran() {
   // ID 1 dynamixel moves to position 512 with velocity 200
  Dxl.setPosition(ID_NUM1, 512, 200);
  delay(1000);  // it has more delay time for slow movement

  // ID 2 dynamixel moves to position 512 with velocity 200
  Dxl.setPosition(ID_NUM2, 512, 200);
  delay(1000);

  // ID 1 dynamixel moves to position 805 with velocity 200
  Dxl.setPosition(ID_NUM1, 805, 200);
  delay(1000);  // it has more delay time for slow movement
  
  // ID 1 dynamixel moves to position 512 with velocity 200
  Dxl.setPosition(ID_NUM1, 512, 200);
  delay(1000);  // it has more delay time for slow movement
  
  // ID 1 dynamixel moves to position 512 with velocity 200
  Dxl.setPosition(ID_NUM1, 215, 200);
  delay(1000);  // it has more delay time for slow movement
  
  // ID 1 dynamixel moves to position 512 with velocity 200
  Dxl.setPosition(ID_NUM1, 512, 200);
  delay(1000);  // it has more delay time for slow movement
}

void tambah(){
  //persamaan 1
 for(i=0; i<=1; i+=0.2)
 {
 X = 4;
 Y = 9+i;
 gerak();
 }
 //persamaan 2
 for(i=0; i<=1; i+=0.2)
 {
 X = 4-i;
 Y = 10;
 gerak();
 }
 //persamaan 3
 for(i=0; i<=1; i+=0.2)
 {
 X = 3;
 Y = 10+i;
 gerak();
 }
 //persamaan 4
 for(i=0; i<=1; i+=0.2)
 {
 X = 3-i;
 Y = 11;
 gerak();
 }
 //persamaan 5
 for(i=0; i<=1; i+=0.2)
 {
 X = 2;
 Y = 11-i;
 gerak();
 }
 //persamaan 6
 for(i=0; i<=1; i+=0.2)
 {
 X = 2-i;
 Y = 10;
 gerak();
 }
 //persamaan 7
 for(i=0; i<=1; i+=0.2)
 {
 X = 1;
 Y = 10-i;
 gerak();
 }
 //persamaan 8
 for(i=0; i<=1; i+=0.2)
 {
 X = 1+i;
 Y = 9;
 gerak();
 }
 //persamaan 9
 for(i=0; i<=1; i+=0.2)
 {
 X = 2;
 Y = 9-i;
 gerak();
 }
 //persamaan 10
 for(i=0; i<=1; i+=0.2)
 {
 X = 2+i;
 Y = 8;
 gerak();
 }
 //persamaan 11
 for(i=0; i<=1; i+=0.2)
 {
 X = 3;
 Y = 8+i;
 gerak();
 }
 //persamaan 12
 for(i=0; i<=1; i+=0.2)
 {
 X = 3+i;
 Y = 9;
 gerak();
 }
}

void persegipanjang(){
   // Persamaan 1
      for (i = 0; i <= 5; i += 0.05) 
      {
        X = i;
        Y = 10;
        gerak();
      }

      // Persamaan 2
      for (i = 0; i <= 1; i += 0.2) {
        X = 5;
        Y = 10 - i;
        gerak();
      }

      // Persamaan 3
      for (i = 0; i <= 5; i += 0.05) {
        X = 5 - i;
        Y = 9;
        gerak();
      }

      // Persamaan 4
      for (i = 0; i <= 1; i += 0.2) 
      {
        X = 0;
        Y = 9 + i;
        gerak();
     }
}

void garis(){
   // Program A
      for (i = 0; i <= 5; i += 0.05) 
      {
        X = i;
        Y = 10;
        gerak();
      }
}

void loop() {  
  delay(500);
  myservo.write(20);
 if(SerialUSB.available()){
    char Cmd = SerialUSB.read();
    SerialUSB.print("Received command: ");
    SerialUSB.println(Cmd);

    
    if(Cmd == 'A'){
      garis();
      
    }else if(Cmd == 'B'){
        tambah();
  
    }else if(Cmd == 'C'){
        persegipanjang();
        
    }else if(Cmd == 'D'){
        setengahlingkaran();
  }
 }
}
