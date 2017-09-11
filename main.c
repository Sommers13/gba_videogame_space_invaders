// ALLISON SOMMERS

#include "mylib.h"
#include "screenimages.h"
#include "objects.h"
#include "text.h"
#include <string.h>


void textProgression() {

     // print out all the number of lives to the screen
     char lives[] = "Lives: ";
     char livesNumber[] = " "; // dummy to store where we're going to put the lives in chars
     livesNumber[0] = (char)(ship.lives + 48); // convert the int to ascii (since there's no way to get more than 9 this works)
     char *livesFullString = strcat(lives, livesNumber); // concatenate the str and the amount
     drawString(150, 105, livesFullString, YELLOW);

     // print out the score to the screen
     char score[] = "Score: ";
     char amount[] = "  "; // dummy to store where we're going to put the score in chars
     // convert to ascii and put in the pseudo-string
     amount[0] = (char) ((ship.score / 10) + 48);
     amount[1] = (char) ((ship.score % 10) + 48);
     char *scoreFullString = strcat(score, amount); // concatenate the str and the amount
     drawString(150, 30, scoreFullString, ORANGE);
}

void getShipCommands() {

     if (KEY_DOWN_NOW(BUTTON_LEFT)) {
          if (ship.x > 0) {
               ship.x--; 
          }
     }

     if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
          if (ship.x < 229) {
               ship.x++;
          }
     }

     if (KEY_DOWN_NOW(BUTTON_A)) {
          fireShipLazer();
     }
}

void drawAliens() {

     // this is the green row of aliens
     if (greenAliensAlive != 0) { // make sure they're still alive
          for (int i=0; i < GREEN_ALIENS_NUMBER; i++) {
               if (greenAliens[i].alive) {
                    drawImage3(greenAliens[i].r, greenAliens[i].c, greenAliens[i].width, greenAliens[i].height, livesalien);
               }
          }
     }

     // this is the red row of aliens
     if (redAliensAlive != 0) { // check if alive
          for (int i=0; i < RED_ALIENS_NUMBER; i++) {
               if (redAliens[i].alive) {
                    drawImage3(redAliens[i].r, redAliens[i].c, redAliens[i].width, redAliens[i].height, alienstandard);
               }
          }
     }

}

void shipLazerControl() {
     if (shipLazer.fired) {

          if (!(KEY_DOWN_NOW(BUTTON_B))) { // only move the lazer if the B button is not being pressed
               
               // redraw ship's lazer
               shipLazer.r -= 3; // make the lazer go up the screen
               shipLazer.c = ship.x + 7; // move lazer with the ship's posiiton
               drawRect3(shipLazer.r, shipLazer.c + LAZER_OFFSET_SHIP, LAZER_WIDTH, LAZER_HEIGHT, shipLazer.color); // redraw lazer


               // check for collision with red aliens
               if (redAliensAlive != 0) {
                    for (int j=0; j < RED_ALIENS_NUMBER; j++) {
                         checkAlienLifeSigns(&shipLazer, &redAliens[j], 0);
                    }
               }
               
               // check for collision with green aliens
               if (greenAliensAlive != 0) {
                    for (int k = 0; k < GREEN_ALIENS_NUMBER; k++) {
                         checkAlienLifeSigns(&shipLazer, &greenAliens[k], 1);
                    }
               }
          
               if (shipLazer.r <= 3) { // check that the lazer isn't on the screen
                    shipLazer.fired = 0;
               }
          } else { // move the lazer with the ship
               shipLazer.c = ship.x + 7; // change lazer column to match ship column
               drawRect3(shipLazer.r, shipLazer.c + LAZER_OFFSET_SHIP, LAZER_WIDTH, LAZER_HEIGHT, shipLazer.color); // redraw lazer
          }
     }
}

void alienLazerControl() {
     if (redAliensAlive != 0) { // fire lazers if there are red aliens left
          fireAlienWeapons();
     } 

     for (int i = 0; i < RED_LAZERS_NUMBER; i++) {
          if (invader_bullets[i].fired) {
               invader_bullets[i].r += 3;
               drawRect3(invader_bullets[i].r, invader_bullets[i].c, 1, LAZER_HEIGHT, invader_bullets[i].color);
          
               // RECTANGULAR COLLISION CHECK ON THE SHIP
               checkShipLifeSigns(&invader_bullets[i], &ship);

               if (invader_bullets[i].r >= 160) {
                    invader_bullets[i].fired = 0;
               }
          }
      }
}



int main() {
     // SET THE MODE TO THE MANDATORY MODE THREE
	REG_DISPCNT = MODE_3 | BG2_EN;

     // initialize start; 1 is start, 0 is not start 
     int start = 1;

     // set everything else to zero
     int frame = 0;
     int movex = 0; // distance the aliens move each time
     int movey = 0; // distance for y
     int stepCounter = 0; // how much the aliens have moved

     // Game loop
     while(1) {
          wait_for_vblank();

          if (KEY_DOWN_NOW(BUTTON_START)) {
               start = 0;
          } else if (KEY_DOWN_NOW(BUTTON_SELECT)) {
               start = 1;
          }

          if (start) { // start/title screen
               drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title);
      
               // reinitialize properly
               frame = 0;
               stepCounter = 0;
               movex = ALIEN_X_MOVEMENT;
               movey = ALIEN_Y_MOVEMENT;

               setupRedAliens(); // create the invaders
               setupRedLazers(); // create the invader bullets
               setupShip(); // create the tank
               setupShipLazer(); // create the tank bullets
               setupGreenAliens();
               totalAliensAlive = RED_ALIENS_NUMBER + GREEN_ALIENS_NUMBER;
               redAliensAlive = RED_ALIENS_NUMBER;
               greenAliensAlive = GREEN_ALIENS_NUMBER;
          } else { // game logic
               frame++;  // increase frame counter
               blank_screen(); // makes it so I don't have to remember to black out things

               if (ship.lives == 0) {
                    drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
                    if (KEY_DOWN_NOW(BUTTON_SELECT) || KEY_DOWN_NOW(BUTTON_START)) {
                         start = 1;
                    }
                    continue;
               } 

               if (totalAliensAlive == 0) {
                    drawImage3(0, 0, WINWIN_WIDTH, WINWIN_HEIGHT, winwin);
                    if (KEY_DOWN_NOW(BUTTON_SELECT) || KEY_DOWN_NOW(BUTTON_START)) {
                         start = 1;
                    }
                    continue;
               }
        
               drawImage3(140, ship.x, SHIP2_WIDTH, SHIP2_HEIGHT, ship2); // draw the ship

               shiftAlienPosition(&frame, &movex, &movey, &stepCounter); // controlling the aliens moving
     
               drawAliens(); // draw the aliens to the screen

               shipLazerControl(); // simple logic for the lazers fired by player
     
               alienLazerControl(); // simple logic for the lazers the aliens fire
          
               getShipCommands(); // move the ship according to user commands

               textProgression(); // print the number of lives and the current score to the bottom of the screen

          } // end game logic
  }
}
