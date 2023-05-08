import javax.swing.JOptionPane;
import java.util.ArrayList;
//Creating arrays to store the grid positions and the positions of the crosses and noughts
ArrayList<Integer> crossPos = new ArrayList<Integer>();
ArrayList<Integer> noughtPos = new ArrayList<Integer>();
ArrayList<String> grid = new ArrayList<String>();

//Creating Images and Buttons for Home Screen
PImage homeScreenLayer1;
PImage multiplayerBtn1;
PImage multiplayerBtn2;
PImage singleplayerBtn1;
PImage singleplayerBtn2;


int turns = 0;

boolean optionSelected = false;
boolean homeScreenVisible = true;
boolean gameScreenVisible = false;
boolean multiplayerHovered;
boolean singleplayerHovered;

void homeScreen(){
  singleplayerHovered = false;
  multiplayerHovered = false;
  background(0,0,125);
  image(homeScreenLayer1,0,0);
  image(multiplayerBtn1,120,325);
  image(singleplayerBtn1,120,400);
  if(mouseX>120 && mouseX<480){
    if(mouseY>325 && mouseY < 425){
      image(multiplayerBtn2,120,325);
      multiplayerHovered = true;
    }
    else if(mouseY>400 && mouseY < 500){
      image(singleplayerBtn2,120,400);
      singleplayerHovered = true;
    }
  }
}


void setup(){
  frameRate(5);
  size(600,600);
  background(255);
  for (int i = 0; i < 9; i++){
    grid.add("empty");
  }
}


boolean emptyCheck(int gridNum){
  if(grid.get(gridNum-1).equals("empty")){
    return true;
  }
  else{
    return false;
  }
}
  

String drawToGrid(){
    //draw Noughts
    String command = "";
    if(turns % 2 == 0){
      //1st Column
      if (mouseX < 200){
        if (mouseY < 200){
          command = "1-Nought";
        }
        else if(mouseY < 400){
          command = "4-Nought";
        }
        else{
          command = "7-Nought";
        }
      }
      //2nd Column
      else if (mouseX < 400){
        if (mouseY < 200){
          command = "2-Nought";
        }
        else if(mouseY < 400){
          command = "5-Nought";
        }
        else{
          command = "8-Nought";
        }
      }
      //3rd Column
      else{
        if (mouseY < 200){
          command = "3-Nought";
        }
        else if(mouseY < 400){
          command = "6-Nought";
        }
        else{
          command = "9-Nought";
        }
      }
    }
    //draw Crosses
    else{
      //1st Column
      if (mouseX < 200){
        if (mouseY < 200){
          command = "1-Cross";
        }
        else if(mouseY < 400){
          command = "4-Cross";
        }
        else{
          command = "7-Cross";
        }
      }
      //2nd Column
      else if (mouseX < 400){
        if (mouseY < 200){
          command = "2-Cross";
        }
        else if(mouseY < 400){
          command = "5-Cross";
        }
        else{
          command = "8-Cross";
        }
      }
      //3rd Column
      else{
        if (mouseY < 200){
          command = "3-Cross";
        }
        else if(mouseY < 400){
          command = "6-Cross";
        }
        else{
          command = "9-Cross";
        }
      }
      
    }
    return(command); 
  }
  
boolean crossWon = false;
boolean noughtWon = false;
  
boolean crossWinChecker(){
  if (crossPos.contains(1) && crossPos.contains(2) && crossPos.contains(3)){
    crossWon = true;
  }
  else if (crossPos.contains(4) && crossPos.contains(5) && crossPos.contains(6)){
    crossWon = true;
  }
  else if (crossPos.contains(7) && crossPos.contains(8) && crossPos.contains(9)){
    crossWon = true;
  }
  //Vertical Wins
  else if (crossPos.contains(1) && crossPos.contains(4) && crossPos.contains(7)){
    crossWon = true;
  }
  else if (crossPos.contains(2) && crossPos.contains(5) && crossPos.contains(8)){
    crossWon = true;
  }
  else if (crossPos.contains(3) && crossPos.contains(6) && crossPos.contains(9)){
    crossWon = true;
  }
  //Diagonal Wins
  else if (crossPos.contains(1) && crossPos.contains(5) && crossPos.contains(9)){
    crossWon = true;
  }
  else if (crossPos.contains(3) && crossPos.contains(5) && crossPos.contains(7)){
    crossWon = true;
  }
  return crossWon;
}

boolean noughtWinChecker(){
  //Horizontal Wins
  if (noughtPos.contains(1) && noughtPos.contains(2) && noughtPos.contains(3)){
    noughtWon = true;
  }
  else if (noughtPos.contains(4) && noughtPos.contains(5) && noughtPos.contains(6)){
    noughtWon = true;
  }
  else if (noughtPos.contains(7) && noughtPos.contains(8) && noughtPos.contains(9)){
    noughtWon = true;
  }
  //Vertical Wins
  else if (noughtPos.contains(1) && noughtPos.contains(4) && noughtPos.contains(7)){
    noughtWon = true;
  }
  else if (noughtPos.contains(2) && noughtPos.contains(5) && noughtPos.contains(8)){
    noughtWon = true;
  }
  else if (noughtPos.contains(3) && noughtPos.contains(6) && noughtPos.contains(9)){
    noughtWon = true;
  }
  //Diagonal Wins
  else if (noughtPos.contains(1) && noughtPos.contains(5) && noughtPos.contains(9)){
    noughtWon = true;
  }
  else if (noughtPos.contains(3) && noughtPos.contains(5) && noughtPos.contains(7)){
    noughtWon = true;
  }
  return noughtWon;
}


boolean won = false;

void draw(){
  if (homeScreenVisible){
    homeScreenLayer1 = loadImage("HomeScreenLayer1.png");
    multiplayerBtn1 = loadImage("multiplayerBtn1.png");
    multiplayerBtn2 = loadImage("multiplayerBtn2.png");
    singleplayerBtn1 = loadImage("singleplayerBtn1.png");
    singleplayerBtn2 = loadImage("singleplayerBtn2.png");
    homeScreen();
  }
  else{
    if (gameScreenVisible){
      background(255);
      gameScreenVisible = false;
    }
    stroke(0);
    strokeWeight(1);
    //Grid setup
    noFill();
    rect(-1,0,601,200);
    rect(-1,200,601,200);
    rect(200,0,200,600);
  }  
}


//Player Setup
void mousePressed(){
  if(singleplayerHovered){
    homeScreenVisible = false;
    gameScreenVisible = true;
    singleplayerHovered = false;
    multiplayerHovered = false;   
  }
  else if(multiplayerHovered){
    homeScreenVisible = false;
    gameScreenVisible = true;
    singleplayerHovered = false;
    multiplayerHovered = false;
  }
  
  if (turns<11 & turns != 0){
    strokeWeight(5);
    if(drawToGrid().equals("1-Nought")){
      if (emptyCheck(1)){        
        stroke(0,0,255);
        ellipse(100,100,190,190);
        grid.set(0,"full");
        noughtPos.add(1);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("2-Nought")){
      if (emptyCheck(2)){
        stroke(0,0,255);
        ellipse(300,100,190,190);
        grid.set(1,"full");
        noughtPos.add(2);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("3-Nought")){
      if (emptyCheck(3)){
        stroke(0,0,255);
        ellipse(500,100,190,190);
        grid.set(2,"full");
        noughtPos.add(3);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("4-Nought")){
      if (emptyCheck(4)){
        stroke(0,0,255);
        ellipse(100,300,190,190);
        grid.set(3,"full");
        noughtPos.add(4);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("5-Nought")){
      if (emptyCheck(5)){
        stroke(0,0,255);
        ellipse(300,300,190,190);
        grid.set(4,"full");
        noughtPos.add(5);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("6-Nought")){
      if (emptyCheck(6)){
        stroke(0,0,255);
        ellipse(500,300,190,190);
        grid.set(5,"full");
        noughtPos.add(6);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("7-Nought")){
      if (emptyCheck(7)){
        stroke(0,0,255);
        ellipse(100,500,190,190);
        grid.set(6,"full");
        noughtPos.add(7);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("8-Nought")){
      if (emptyCheck(8)){
        stroke(0,0,255);
        ellipse(300,500,190,190);
        grid.set(7,"full");
        noughtPos.add(8);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("9-Nought")){
      if (emptyCheck(9)){
        stroke(0,0,255);
        ellipse(500,500,190,190);
        grid.set(8,"full");
        noughtPos.add(9);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("1-Cross")){
      if (emptyCheck(1)){
        stroke(255,0,0);
        line(0,0,200,200);
        line(200,0,0,200);
        grid.set(0,"full");
        crossPos.add(1);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("2-Cross")){
      if (emptyCheck(2)){
        stroke(255,0,0);
        line(200,0,400,200);
        line(400,0,200,200);
        grid.set(1,"full");
        crossPos.add(2);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("3-Cross")){
      if (emptyCheck(3)){
        stroke(255,0,0);
        line(400,0,600,200);
        line(600,0,400,200);
        grid.set(2,"full");
        crossPos.add(3);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("4-Cross")){
      if (emptyCheck(4)){
        stroke(255,0,0);
        line(0,200,200,400);
        line(200,200,0,400);
        grid.set(3,"full");
        crossPos.add(4);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("5-Cross")){
      if (emptyCheck(5)){
        stroke(255,0,0);
        line(200,200,400,400);
        line(400,200,200,400);
        grid.set(4,"full");
        crossPos.add(5);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("6-Cross")){
      if (emptyCheck(6)){
        stroke(255,0,0);
        line(400,200,600,400);
        line(600,200,400,400);
        grid.set(5,"full");
        crossPos.add(6);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("7-Cross")){
      if (emptyCheck(7)){
        stroke(255,0,0);
        line(0,400,200,600);
        line(0,600,200,400);
        grid.set(6,"full");
        crossPos.add(7);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("8-Cross")){
      if (emptyCheck(8)){
        stroke(255,0,0);
        line(200,400,400,600);
        line(400,400,200,600);
        grid.set(7,"full");
        crossPos.add(8);
        turns = turns + 1;
      }
    }
    else if(drawToGrid().equals("9-Cross")){
      if (emptyCheck(9)){
        stroke(255,0,0);
        line(400,400,600,600);
        line(600,400,400,600);
        grid.set(8,"full");
        crossPos.add(9);
        turns = turns + 1;
      }
    }
    print(crossPos);
    print(noughtPos);
  }
  else{
      turns = turns + 1;
      
    }
  
  noughtWinChecker();
  crossWinChecker();
  
  if (won == false){
    if (noughtWon){
      JOptionPane.showMessageDialog(null,"Noughts have won!");
      turns = 10;
      //background(0,0,255);
      won = true;
    }
    else if (crossWon){
      JOptionPane.showMessageDialog(null,"Crosses have won!");
      turns = 10;
      //background(255,0,0);
      won = true;
    }
    else if((turns == 9) && (crossWon == noughtWon == false)){
      JOptionPane.showMessageDialog(null, "It's a draw!");
      //background(255);
      won = true;
    }
  }
}


//reference https://www.dotnetperls.com/convert-arraylist-string-java
String convertToString(ArrayList<Integer> numbers) {
  StringBuilder builder = new StringBuilder();
  // Append all Integers in StringBuilder to the StringBuilder.
  for (int number : numbers) {
    builder.append(number);
    builder.append(":");
  }
  // Remove last delimiter with setLength.
  builder.setLength(builder.length() - 1);
  return builder.toString();
    }

void dug(){
  
}
