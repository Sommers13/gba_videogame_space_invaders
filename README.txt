/*
* ALLISON SOMMERS
* 2110 HW9
* README DOCUMENT FOR VIDEO GAME

Button Controls:
- Use the right and left arrow keys to move the spaceship side to side. You cannot move up or down.
- Press A to fire a lazer.
- Hold B down to keep the lazer from going up and down in the y direction. 
	- If you move the tank, the lazer will track with it. 
	- Release B to allow the lazer to advance up the y-axis again.
- At the title screen, hit start to play the game.
- Hit select while in game to restart.
- When either the game over or triumph screen display, hit select or start to return to title/start screen.
- Hitting the other buttons should do nothing.

Alien Behavior:
- The red aliens fire semi-randomly. The more aliens you defeat, the more frequently they fire.
- Killing a red alien will increase your score by 5 points.
- The green aliens do not fire at you. Killing one will increase your score by one point, and you will gain an extra life. However, this makes the red aliens fire more rapidly.
- The red aliens will only move from right to left across the top of the screen in a fixed configuration.
- The green aliens will move from right to left and up and down over the screen in a fixed configuration.
- It is impossible for an alien on alien or alien on ship collision to happen.

Text Progression:
- Throughout the game (excluding start, gameover, and win screens), the ship's life and score count are displayed at the bottom of the screen.
- At the beginning of the game, you have 1 life annd a score of 0.
- Maximum number of lives you can obtain is 1 + amount of green aliens.
- Maximum number of points you can obtain is (the amount of green aliens + (5 * the amount of red aliens))
*/
