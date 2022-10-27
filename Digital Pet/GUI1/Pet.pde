public  class  Pet{
  //description
  String   name;
  int      age;
  int      stroke;
  int      beat;
  int      time;
  
  //GUI 
  PImage   img;
  PVector  current;
  int      beginGameTime;
  //move/smile properties
  int      timeS=0;
  int      timeM=0;
  //move properties
  int      resist=  -5  ;
  int      acc=     20;
  int      speed=   0;
  int      dir=     0;
  int      s=      200;
  int      r=      s/4;
  boolean  canDecide=  true;
  boolean  canSmile=   false;
  boolean  canMove=    false;
  boolean  canSpeak=    false;
  //for ages and beats
  int    speedUp=      20;
  
  public  void  initialPet(){
    float  rx=  random(200,300);
    float  ry=  random(200,300);
    current=new PVector(rx, ry);
    img=loadImage("pet1.png");
    img.resize(s,0);
    ageDecideGUI();
    beginGameTime=  second();
  }
  
  private  void  ageDecideGUI(){
    switch  (age){
      case  1:
        canMove=  true;
        break;
      case  2:
        canMove=  true;
        canSmile=  true;
        acc=       15;
        break;
      case  3:
        canSmile=  true;
        break;
      case  4:  //die  
        img= loadImage("pet0.png");
        img.resize(200,0);
    }
  }
  
  public  void  getData(Table table,  int  i){
    TableRow r=  table.getRow(i);
    name=  r.getString("name");
    age=   r.getInt("age");
    stroke= r.getInt("stroke");
    beat=   r.getInt("beaten");
    time=   r.getInt("time");
    println("Pet's data got: ");
    println("name: "+name+" age: "+age+" stroke: "+stroke+" beat: "+beat+" time: "+ time);
  }
  
  public  void  createPet(String  n){
    name=  n;
    age=   1;
    stroke= 0;
    beat=   0;
    time=   0;
    println("Pet created: ");
    println("name: "+name+" age: "+age+" stroke: "+stroke+" beat: "+beat+" time: "+ time);
  }
  
  public  void   decide(){
    timeS=1;
    timeM=1;
    float  dis=sqrt(pow((mouseX-current.x),2)+pow((mouseY-current.y),2));
    if(dis<r){
      if(mouseX<current.x)
        dir=1;  //Right
      else
        dir=-1;
      canDecide=  false;
      canSpeak=   true;
    }
  }
    public  void  smile(){
    if(canSmile){
      if(timeS<6){
          img=  loadImage("pet"+timeS+".png");
          img.resize(s,0);
      }
      else{
        canDecide=true;
        img=  loadImage("pet"+1+".png");
        img.resize(s,0);
      }
      timeS++;
    }
  }

  
  public  void  move(){
    if(canMove){
      int  force=0;
      if(timeM<3)
          force=  (acc+resist)*dir;
      else
          force=  resist*dir;
      speed+=force;
      current.x+=speed;
      
      if(current.x>400)//boundary
        current.x=0;
      if(current.x<0)//boundary
        current.x=400;
        
      if(speed*dir<=0){
        dir=0;
        canDecide=true;
      }
      timeM++;
      println("speed: "+speed+" force: "+force+" time: "+timeM+" dir: "+dir);
    }
  }
  
  //count the number of effective beats
  public  void  count(){
    beat++;
    println("beat: "+ beat);
  }
  //introduce itself in page 3
  public  void  intro(){
    int  txtS=  18;
    textSize(txtS);
    text("I'm "+name, current.x+0.2*s, current.y); 
    text("We've spent  "+ p.time+ " min together", current.x+0.2*s, current.y+  txtS*1.2); 
    if(age==4){
      if(beat>10)
        text("You beat me  "+ p.beat+ " , It hurts", current.x+0.2*s, current.y+  txtS*2.4);
      else
        text("I'm too old  ", current.x+0.2*s, current.y+  txtS*3.6);
      text("So it's time to say goodbye. ", current.x+0.2*s, current.y+  txtS*4.8);
      }
    else if(age==2)
      text("I'm excited to be your pal", current.x+0.2*s, current.y+  txtS*2.4);
    fill(0, 102, 153);
  }
  
  //decide age according to time, strokes and beats
  public  void  decideAge(){
    if(p.age<4){
      time=  time+  (second()-beginGameTime)*speedUp/60;
      println((second()-beginGameTime)*speedUp/60);
      //aging
      if(time>20)
          age=2;
      if(time>150)
          age=3;
      //if beats is 3 times larger than strokes, then die
      //if old enough, die
      if(beat>10  ||  time>180)
        age=4;
    }
  }
}
