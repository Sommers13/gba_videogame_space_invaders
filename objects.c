// ALLISON SOMMERS

#include "objects.h"
#include "screenimages.h"
#include "mylib.h"
#include <stdlib.h>

// initialize the red aliens
void setupRedAliens() {
  	for (int i = 0; i < RED_ALIENS_NUMBER; i++) {
    		redAliens[i].r = RED_START_ROW;
    		redAliens[i].c = RED_START_COL + ((ALIENSTANDARD_WIDTH + 5)*i);
    		redAliens[i].alive = 1;
    		redAliens[i].width = ALIENSTANDARD_WIDTH;
    		redAliens[i].height = ALIENSTANDARD_HEIGHT;
  	}
}

void setupGreenAliens() {
  	for (int i=0; i < GREEN_ALIENS_NUMBER; i++) {
    		greenAliens[i].r = GREEN_START_ROW;
    		greenAliens[i].c = GREEN_START_COL + ((LIVESALIEN_WIDTH + 5)*i);
    		greenAliens[i].alive = 1;
    		greenAliens[i].width = LIVESALIEN_WIDTH;
    		greenAliens[i].height = LIVESALIEN_HEIGHT;
  	}
}

/* Initialize the tank. Starts out with 3 lives */
void setupShip() {
     ship.r = SHIP_START_ROW;
     ship.x = SHIP_START_COL;
     ship.lives = 1;
     ship.score = 0;
}

/* Initialize all the invader bullets. 
   fired = 0 -> not fired
   fired = 1 -> fired */
void setupRedLazers() {
  	for (int i=0; i < RED_LAZERS_NUMBER; i++) {
    		invader_bullets[i].r = 0;
    		invader_bullets[i].c = 0;
    		invader_bullets[i].fired = 0;
    		invader_bullets[i].color = RED;
  	}
}

// setup the ship's lazers, everything to default zero
void setupShipLazer() {
    	shipLazer.r = 0;
    	shipLazer.c = 0;
    	shipLazer.fired = 0;
    	shipLazer.color = BLUE;
}

// fire the aliens' bullets
void fireAlienWeapons() {

     // if there are a lot of alive aliens, they fire slowly
     // firing speed goes up the less aliens are left as they get desperate
     int fire = rand() % (10 * totalAliensAlive);

	// for getting out of the for loop
	int flag = 0;

     for (int i = 0; ((i < RED_LAZERS_NUMBER) && (!flag)); i++) {
          if (!invader_bullets[i].fired) {
               if (fire <= 3) {

                    // Find a random invader that is alive.
                    int alien;
                    do { 
                         alien = rand() % RED_ALIENS_NUMBER;
                    } while (!redAliens[alien].alive);
        
               	invader_bullets[i].r = RED_START_ROW + LAZER_OFFSET_ALIEN;
               	invader_bullets[i].c = redAliens[alien].c + LAZER_OFFSET_ALIEN;
               	invader_bullets[i].fired = 1;
               	flag = 1; // get out of loop once the alien has fired
      		}
    		}	
  	}
}


void fireShipLazer() {
	if (!shipLazer.fired) { // only fire one lazer at a time
    		shipLazer.r = ship.r;
    		shipLazer.c = ship.x + LAZER_OFFSET_SHIP;
    		shipLazer.fired = 1;
	}
}

void shiftAlienPosition(int *frame, int *movex, int *movey, int *stepCounter) {
	int framemod = ALIENSPEED;
	int movechange = 10;
	int check = 0;

     if (*frame % framemod == 0) {
     	
		for (int i = 0; i < RED_ALIENS_NUMBER; i++) { // move the red ones
	          redAliens[i].c += *movex;
	     }

	     for (int j = 0; j < GREEN_ALIENS_NUMBER; j++) { // move the green ones
	          greenAliens[j].c -= *movex;
	          greenAliens[j].r += 3* (*movey);
	     }

       	if (*movex >= 0) {
        		*stepCounter = *stepCounter + 1; // couldn't just use *stepCounter++ because that would be too easy (said the variable was never used)
             	if (*stepCounter / ALIEN_MOVES == 1) { // reverse direction when we've hit the end
               	*movex = -1*movechange;
              	}
               if (*stepCounter == check) { // reverse direction when we've hit the end
                	*movex = movechange;
              	}
      	} else {
        		*stepCounter = *stepCounter - 1;
              	if (*stepCounter / ALIEN_MOVES == 1) { // reverse direction when we've hit the end
              		*movex = -1*movechange;
               }
               if (*stepCounter == check) { // reverse direction when we've hit the end
                	*movex = movechange;
               }
         	}

  		if (*stepCounter % 3 == 0) { // reverse the green aliens' y direction; this can be used with x direction to create cool motions
        		*movey = *movey * -1;                    
          }
	}
}

// Check whether the ship's lazer collided with an alien
// Flag tells which alien it is. 0 = red, 1 = green.
// If there is a collision, nullify the ship's current lazer so it can fire again, set the alien to not alive, and mess with lives and score.
// Also pointeres practice!!
void checkAlienLifeSigns(Lazer *lazer, Alien *alien, int flag) {
     if (alien->alive) { // don't do anything if the lazer is nullified

		// check if the lazer is within the alien's coordinates
          if ((alien->r + 10 >= lazer->r) && (alien->r <= lazer-> r + LAZER_HEIGHT) && (alien->c <= lazer->c) && (alien->c + 10 >= lazer->c)) {
               alien->alive = 0;
               totalAliensAlive--;
               lazer->fired = 0;

               if (flag == 1) { // green alien
                    greenAliensAlive--;
                    ship.lives++; // extra lives
                    ship.score++;
               } 

               if (flag == 0) { // red alien
                    redAliensAlive--;
                    ship.score = ship.score + 5; // more points for killing a red
               }
          } 
     }
}

// See if the ship's been hit with an alien's lazer
// If the ship's been hit, decrease amount of lives and nullify the lazer.
void checkShipLifeSigns(Lazer *lazer, Ship *ship) {
     if (lazer->fired) { // don't do anything if the lazer is nullified

		// this requires less checking than with the aliens because we don't have any potential collisions from below
	if (lazer-> r+3 >= ship-> r && (lazer->c >= ship->x && lazer->c <= ship->x + SHIP2_WIDTH)) {
               lazer->fired = 0;
               ship->lives--;
          }
     }
}
