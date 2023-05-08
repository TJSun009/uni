import javax.swing.JOptionPane;
import java.util.ArrayList;

void draw() {
  if (homeScreenVisible) {
    homeScreen();
    hovered();
  }
  else{
    if (gameScreenDisplayed) {
      turns +=1;
      gameScreenDisplayed = false;
      drawn = false;
    }
  }
  winProcedure();
  
  if (!multiplayerActive){
    computerScreenUpdate();
  }
}

void settings() {
  size(600, 600);
}

void setup() {
  frameRate(5);
  background(255);
  initArrays();
  surface.setTitle("Noughts x Crosses");
  PImage Icon = loadImage("Icon.png");
  surface.setIcon(Icon);
}


//Player Setup
void mousePressed(){
  if (singleplayerHovered && turns == 0) {
    startGame();
    multiplayerActive = false;
    turns +=1;
  } else if (multiplayerHovered && turns == 0) {
    startGame();
    multiplayerActive = true;
  }

  
  if (!multiplayerActive){
    playerScreenUpdate();
  }else{
    multiplayerScreenUpdate();
  }
  
  System.out.println(turns);
  System.out.println(freePos);
  System.out.println(grid);
}
