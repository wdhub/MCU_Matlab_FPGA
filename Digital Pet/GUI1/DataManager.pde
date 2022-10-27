public  class  DataManager{
  Table table;
  //read data from document
  void  read(){
    table=  loadTable("new1.csv",  "header");
  }
  
  //check and create object
  //if exsist, read
  //if not, write
  Pet  check(String name){
    Pet      p=new  Pet();
    //tell if it is a default key
    if(name.equals("")){
      p=null;
      println("It's not a name, mate.");
    }
    else{
    //search
    int  i=0;
    for(i=0;  i<  table.getRowCount();  i++){
      String temp=  table.getString(i, "name");
      println(temp+" "+i);
      if(temp.equals(name)){
        p.getData(table, i);
        println("dataManager: this is an existed pet");
        println("name: "+name+" age: "+table.getInt(i, "age")+" stroke: "+table.getInt(i, "stroke")+" beat: "+table.getInt(i, "beaten")+" time: "+ table.getInt(i, "time"));
        break;
      }
    }
    //new pet
    if(i==  table.getRowCount()){
      TableRow row = table.addRow();
      row.setString("name", name);
      row.setInt("age", 1);
      row.setInt("stroke", 0);
      row.setInt("beaten", 0);
      row.setInt("time", 0);
      p.createPet(name);
      saveTable(table,  "new1.csv");
      table=null;
    }
    p.initialPet();
    }
    return  p;
  }
  
  //save object to the ducument
  void  saveData(){
    p.decideAge();
    println("age: "+p.age);
    //search
    int  i=0;
    table=  loadTable("new1.csv",  "header");
    
    for(i=0;  i<  table.getRowCount();  i++){
      String temp=  table.getString(i, "name");
      if(temp.equals(p.name)){
        TableRow r=  table.getRow(i);
        r.setInt("age", p.age);
        r.setInt("stroke", p.stroke);
        r.setInt("beaten", p.beat);
        r.setInt("time", p.time);
        break;
      }
    }
    //save table
    saveTable(table,  "new1.csv");
  }
  

}
