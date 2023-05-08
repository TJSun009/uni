//Libraries
import javax.swing.JOptionPane;
import java.util.ArrayList;

class gridTile {
  int pos, x, y;
  String value = "null";
  boolean empty = true;
}
//Creating arrays to store the grid positions and the positions of the crosses and noughts
ArrayList<Integer> crossPos = new ArrayList<Integer>();
ArrayList<Integer> noughtPos = new ArrayList<Integer>();
ArrayList<gridTile> grid = new ArrayList<gridTile>();
ArrayList<Integer> freePos = new ArrayList<Integer>();

//Creating Images and Buttons for Home Screen
PImage HomeScreenLayer1, HomeScreenLayer2, multiplayerBtn1, multiplayerBtn2, singleplayerBtn1, singleplayerBtn2;

//Create Sprites for Game Screen
PImage noughtImg, crossImg; 
int turns = 0;
int compChoice, choice;

boolean homeScreenVisible = true;
boolean gameScreenVisible, optionSelected, multiplayerActive, gameScreenDisplayed, drawn = false;
boolean multiplayerHovered, singleplayerHovered = false;
boolean crossWon, noughtWon, won  = false;

void reset(){
  crossPos.clear();
  noughtPos.clear();
  grid.clear();
  freePos.clear();
  turns = 0;
  
  homeScreenVisible = true;
  gameScreenVisible = optionSelected = multiplayerActive = gameScreenDisplayed = drawn = false;
  multiplayerHovered = singleplayerHovered = false;
  crossWon = noughtWon = won  = false;
}

void homeScreen() {
  HomeScreenLayer1 = loadImage("HomeScreenLayer1.jpg");
  HomeScreenLayer2 = loadImage("HomeScreenLayer2.png");
  multiplayerBtn1 = loadImage("multiplayerBtn1.png");
  multiplayerBtn2 = loadImage("multiplayerBtn2.png");
  singleplayerBtn1 = loadImage("singleplayerBtn1.png");
  singleplayerBtn2 = loadImage("singleplayerBtn2.png");
  noughtImg = loadImage("crossImg.png");
  crossImg = loadImage("noughtImg.png");
  background(HomeScreenLayer1);
  image(HomeScreenLayer2, 0, 0);
  image(multiplayerBtn1, 120, 325);
  image(singleplayerBtn1, 120, 400);
}

void hovered(){
  if (mouseX > 120 && mouseX < 480) {
    if (mouseY > 350 && mouseY < 395) {
      image(multiplayerBtn2, 120, 325);
      multiplayerHovered = true;
    } else if (mouseY > 425 && mouseY < 470) {
      image(singleplayerBtn2, 120, 400);
      singleplayerHovered = true;
    }
  }
}

void initArrays(){
  int x = 0, y = 0, i = 0;
  while(y < 401){
    while(x < 401){
      if(x % 200 == 0 && y % 200 == 0){
        gridTile currentTile = new gridTile();
        currentTile.pos = (i + 1);
        
        currentTile.x = x;
        currentTile.y = y;
        
        System.out.print(i);
        grid.add(currentTile);
        freePos.add(i+1);
      }
      
      i+=1;
      x += 200;
    }
    x = 0;
    y += 200;
  }
}

boolean emptyCheck(gridTile tile) {
  println(tile.empty);
  if (tile.empty) {
    freePos.remove(new Integer(tile.pos));
    tile.empty = false;
    println(tile.empty);
    println("empty true");
    return true;
  }else{
    println("empty false");
    return false;
  }
}

gridTile position(){
  gridTile tile = new gridTile();
  
  if (mouseX < 201){
      if (mouseY < 201){
        tile = grid.get(0);
      }
      else if(mouseY < 401){
        tile = grid.get(3);
      }
      else if(mouseY < 601){
        tile = grid.get(6);
      }
    }
    else if (mouseX < 401){
      if (mouseY < 201){
        tile = grid.get(1);
      }
      else if(mouseY < 401){
        tile = grid.get(4);
      }
      else if(mouseY < 601){
        tile = grid.get(7);
      }
    }
    else{
      if (mouseY < 201){
        tile = grid.get(2);
      }
      else if(mouseY < 401){
        tile = grid.get(5);
      }
      else if(mouseY < 601){
        tile = grid.get(8);
      }
    }
    return(tile);
}


gridTile drawToGrid() {
  gridTile tile = new gridTile();
  
  if(multiplayerActive){
    tile = position();
    if (turns % 2 == 0) {
      tile.value = "O";
    }
    else{
      tile.value = "X";
    }
  }else if(!multiplayerActive){
    if (turns % 2 == 0) {
      tile = position();
      tile.value = "O";
    }
    else{
      choice = (int)Math.floor(Math.random()*(freePos.size()));
      compChoice = (int)freePos.get(choice);
      tile = grid.get(compChoice-1);
      tile.value = "X";
    }
  }
  drawn = true;
  return(tile);
}



boolean crossWinChecker() {
  if (crossPos.contains(1) && crossPos.contains(2) && crossPos.contains(3)) {
    crossWon = true;
  } else if (crossPos.contains(4) && crossPos.contains(5) && crossPos.contains(6)) {
    crossWon = true;
  } else if (crossPos.contains(7) && crossPos.contains(8) && crossPos.contains(9)) {
    crossWon = true;
  }
  //Vertical Wins
  else if (crossPos.contains(1) && crossPos.contains(4) && crossPos.contains(7)) {
    crossWon = true;
  } else if (crossPos.contains(2) && crossPos.contains(5) && crossPos.contains(8)) {
    crossWon = true;
  } else if (crossPos.contains(3) && crossPos.contains(6) && crossPos.contains(9)) {
    crossWon = true;
  }
  //Diagonal Wins
  else if (crossPos.contains(1) && crossPos.contains(5) && crossPos.contains(9)) {
    crossWon = true;
  } else if (crossPos.contains(3) && crossPos.contains(5) && crossPos.contains(7)) {
    crossWon = true;
  }
  return crossWon;
}

boolean noughtWinChecker() {
  //Horizontal Wins
  if (noughtPos.contains(1) && noughtPos.contains(2) && noughtPos.contains(3)) {
    noughtWon = true;
  } else if (noughtPos.contains(4) && noughtPos.contains(5) && noughtPos.contains(6)) {
    noughtWon = true;
  } else if (noughtPos.contains(7) && noughtPos.contains(8) && noughtPos.contains(9)) {
    noughtWon = true;
  }
  //Vertical Wins
  else if (noughtPos.contains(1) && noughtPos.contains(4) && noughtPos.contains(7)) {
    noughtWon = true;
  } else if (noughtPos.contains(2) && noughtPos.contains(5) && noughtPos.contains(8)) {
    noughtWon = true;
  } else if (noughtPos.contains(3) && noughtPos.contains(6) && noughtPos.contains(9)) {
    noughtWon = true;
  }
  //Diagonal Wins
  else if (noughtPos.contains(1) && noughtPos.contains(5) && noughtPos.contains(9)) {
    noughtWon = true;
  } else if (noughtPos.contains(3) && noughtPos.contains(5) && noughtPos.contains(7)) {
    noughtWon = true;
  }
  return noughtWon;
}

void winProcedure(){
  Object[] options = {"Play Again", "Quit"};
  int gameOver = 0;
  if (!won && drawn){
    if (noughtWon) {
      gameOver = JOptionPane.showOptionDialog(null, "Noughts have won!", "Game Over!", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, null);
      turns = 20;
      won = true;
      gameScreenVisible = false;
    } else if (crossWon) {
      gameOver = JOptionPane.showOptionDialog(null, "Crosses have won!", "Game Over!", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, null);
      turns = 20;
      won = true;
      gameScreenVisible = false;
    } else if ((turns == 10) && crossWon == false && noughtWon == false) {
      gameOver = JOptionPane.showOptionDialog(null, "It's a draw!", "Game Over!", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, null);
      turns = 20;
      won = true;
      gameScreenVisible = false;
    }
  }
  
  if (won == true){
    if (gameOver == JOptionPane.YES_OPTION){
      background(255);
      reset();
      setup();
    }
    else if (gameOver == JOptionPane.NO_OPTION){
      exit();
    }
  }
  noughtWinChecker();
  crossWinChecker();
}

void gridSetup(){
  background(HomeScreenLayer1);
  noFill();
  stroke(255);
  rect(-1, 0, 601, 200);
  rect(-1, 200, 601, 200);
  rect(200, 0, 200, 600);
}

void computerScreenUpdate(){
  if (turns < 11 && turns != 0) {
    gridTile tile = drawToGrid();
    if(emptyCheck(tile)){
      System.out.printf("The tiles x is %d and y is %d\npos: %d\n",tile.x,tile.y,tile.pos);
      image(crossImg, tile.x, tile.y);
      crossPos.add(tile.pos);
      turns += 1;
    }
  }
}

void playerScreenUpdate(){
  if (turns < 11 && turns != 0) {
    if (!multiplayerActive) {
    gridTile tile = drawToGrid();
    if(emptyCheck(tile)){
        System.out.printf("The tiles x is %d and y is %d\npos: %d\n",tile.x,tile.y,tile.pos);
        image(noughtImg, tile.x, tile.y);
        noughtPos.add(tile.pos);
        turns += 1;
      }
    }
  }
}

void startGame(){
  gridSetup();
  homeScreenVisible = false;
  gameScreenVisible = true;
  singleplayerHovered = false;
  multiplayerHovered = false;
  gameScreenDisplayed = true;
}

void multiplayerScreenUpdate(){
  if (turns < 11 && turns != 0) {
    if(multiplayerActive){
      gridTile tile = drawToGrid();
      if(emptyCheck(tile)){
        if(tile.value.equals("X")){
          System.out.printf("The tiles x is %d and y is %d\npos: %d\n",tile.x,tile.y,tile.pos);
          image(crossImg, tile.x, tile.y);
          crossPos.add(tile.pos);
          turns += 1;
        }else if(tile.value.equals("O")){
          System.out.printf("The tiles x is %d and y is %d\npos: %d\n",tile.x,tile.y,tile.pos);
          image(noughtImg, tile.x, tile.y);
          noughtPos.add(tile.pos);
          turns += 1;
        }
      }
    }
  }
  print(crossPos);
  print(noughtPos);
}
