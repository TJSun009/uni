import javax.swing.JOptionPane;
import java.util.ArrayList;

void draw() {
  if (homeScreenVisible) {
    homeScreen();
    hovered();
  } else {
    if (gameScreenDisplayed) {
      turns +=1;
      gameScreenDisplayed = false;
    }
  }

  if (!multiplayerActive && turns % 2 != 0) {
    computerScreenUpdate();
  }

  winProcedure();
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
void mousePressed() {
  if (singleplayerHovered && turns == 0) {
    startGame();
    multiplayerActive = false;
  } else if (multiplayerHovered && turns == 0) {
    startGame();
    multiplayerActive = true;
  }


  if (!multiplayerActive && turns % 2 == 0) {
    playerScreenUpdate();
  } else {
    multiplayerScreenUpdate();
  }

  winProcedure();
}
