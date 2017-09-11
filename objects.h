// ALLISON SOMMERS


// THIS IS THE STUFF YOU CAN MODIFY TO CHANGE GAME EXPERIENCE

// DO NOT EXCEED THIS NUMBER
#define MAX_NUM_ALIENS_GBA_CAN_HANDLE_IN_MODE_3 9

// increase for faster alien movement speed, decrease for slower alien movement speed
#define ALIENSPEED 50

#define SHIP_START_ROW 140
#define SHIP_START_COL 190

#define ALIEN_MOVES 12
#define ALIEN_X_MOVEMENT 10
#define ALIEN_Y_MOVEMENT 3

#define RED_ALIENS_NUMBER 4
#define RED_START_ROW 10
#define RED_START_COL 10
#define RED_LAZERS_NUMBER 5

#define GREEN_ALIENS_NUMBER 5
#define GREEN_START_ROW 80
#define GREEN_START_COL 140

#define LAZER_HEIGHT 3
#define LAZER_WIDTH 1
#define LAZER_OFFSET_ALIEN 5
#define LAZER_OFFSET_SHIP -2

typedef struct alien {
     int r;
     int c;
     int width;
     int height;
     int alive;
} Alien;

typedef struct ship {
     int r;
     int x;
     int lives;
     int score;
} Ship;

typedef struct lazer {
     int r;
     int c;
     int fired;
     unsigned short color;
} Lazer;

// GLOBAL OBJECTS
Alien redAliens[RED_ALIENS_NUMBER];
Alien greenAliens[GREEN_ALIENS_NUMBER];
Lazer invader_bullets[RED_LAZERS_NUMBER];
Ship ship;
Lazer shipLazer;
int totalAliensAlive;
int redAliensAlive;
int greenAliensAlive;

// FUNCTION PROTOTYPES
void setupGreenAliens();
void setupRedAliens();
void setupShip();
void setupRedLazers();
void setupShipLazer();
void fireShipLazer();
void fireAlienWeapons();
void checkAlienLifeSigns(Lazer *lazer, Alien *alien,  int flag); 
void checkShipLifeSigns(Lazer *lazer, Ship *ship);
void shiftAlienPosition(int *frame, int *movex, int *movey, int *stepCounter);
