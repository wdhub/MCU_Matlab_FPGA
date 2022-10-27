import controlP5.*;
import processing.serial.*;
//seiral port
Serial myPort;      // The serial port
int inByte = -1;    // Incoming serial data
ControlP5 cp5;
PImage   bgd;
PImage   pet;
String   name="";//name of the pet, for page 1
Pet      p=new  Pet();
DataManager  dm=new  DataManager();
Textfield  txt;
int      numPage=1;

void setup() {
  background(0);
  size(500,400);
  bgd=loadImage("bgd.GIF");
  dm.read();
  page1GUI();
  //serial setup
  setSerial();
}

void  setSerial() {
  int  serial_baud_rate = 9600;
  String  portName=  "COM3";
  myPort = new Serial(this, portName, serial_baud_rate);
   
}

void draw(){
  switch (numPage){
  case  1:
    page1();
    break;
  case  2:
    page2(); 
    break;
  case  3:
    page3(); 
    break;
  default:
    page1();
  }
}
void  page1GUI(){
  cp5 = new ControlP5(this);
  PFont font = createFont("arial",20);
  txt=  cp5.addTextfield("name")
     .setPosition(width/2-100,height/3-100)
     .setSize(200,40)
     .setFont(font)
     .setFocus(true)
     .setColor(color(255,255,255))
     ;
}
void  page1(){
  image(bgd,  0,  0);
}

void  keyPressed(){  
    //search and turn
    if(keyCode==  ENTER){
      name=  cp5.get(Textfield.class,"name").getText();
      p=  dm.check(name);
      if(p!=null){
        numPage=2;
        txt.hide();
      }
    }
    //save and exit
  if(keyPressed)
    if(keyCode== DELETE){
      dm.saveData();
      for(int  i=0;  i  <100;  i++)
        myPort.write(4);
      exit();
    }
    
  }
  
void  page2(){
  //simulate random background LATER
  bgd=loadImage("bgd2.JPG");
  bgd.resize(0,width);
  image(bgd,  0,  0);
  //TEXT
  textSize(24);
  text("SOUL IMPLANTING ... ",  height/2-100,  width/2-100); 
  fill(255);
  //simulate waiting
  if(second()%10==0){
    bgd=loadImage("bgd4.JPG");
    numPage=3;
  }
}

void  page3(){
  image(bgd,  0,  0);
  page3Act();
  //serial com
  page3Serial();
  delay(50);
      
}


void page3Act(){
  if(p.canDecide)
    p.decide();
  if(p.dir!=0){
    p.smile();
    p.move();
    p.intro();p.intro();
  
  }
  image(p.img,  p.current.x- p.s*0.5,   p.current.y- p.s*0.5);
  //println("x: "+p.current.x+  "y: "+p.current.y);
  //delay(10);
}
void  page3Serial(){
  if (true) {
    //receive
    byte[] inBuffer = new byte[100];
    inBuffer = myPort.readBytes();
    if(inBuffer!=null){
      println(inBuffer);
      //twice=once
      if(inBuffer[0]!=  0&&  p.age<4)
        p.count();  
    }
    //send
    myPort.write(p.age);
  }
    
}
