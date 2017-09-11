// ALLISON SOMMERS

#include "mylib.h"

u16 *videoBuffer = (u16 *) 0x6000000;

void setPixel(int r, int c, u16 color) {
     videoBuffer[240*r+c] = color;
}

void drawRect(int r, int c, int width, int height, u16 color) {
     for (int i = 0; i < height; i++) { // loop through each row
          for (int j = 0; j < width; j++) { // each column
               setPixel(r+i, j+c, color);
          }
     }
}

// draw rectangle using DMA
void drawRect3(int r, int c, int width, int height, u16 color) {
     for (u16 row = 0; row < height; row++) {
          REG_DMA3SRC = (vu32) &color; // Source
          REG_DMA3DAD = (vu32) &(videoBuffer[OFFSET(row + r, c, 240)]); // Destination
          REG_DMA3CNT = width | DMA_SOURCE_FIXED | DMA_ON; // Count and start
     }
}


void delay(int how_long) {
     for (volatile int i = 0; i < how_long * 1000; i++) {
     }
}

void wait_for_vblank() {
     u16 *scan = SCANLINECOUNTER;

     while (*scan > 160) {
          ;
     } // in vblank, wait to exit
     while (*scan <= 160) {
          ;
     } // wait for beginning of next vblank
}

// blank out the screen using the DMA
void blank_screen() {
     REG_DMA3SRC = (vu32) BLACK;
     REG_DMA3DAD = (vu32) videoBuffer;
     REG_DMA3CNT = 240*160 | DMA_ON; 
}

// Draw an image using DMA
void drawImage3(int r, int c, int width, int height, const u16* image) {
     for (u16 row = 0; row < height; row++) {
          REG_DMA3SRC = (vu32) (image + (width*row)); // Source
          REG_DMA3DAD = (vu32) &(videoBuffer[OFFSET(row + r, c, 240)]); // Destination
          REG_DMA3CNT = width | DMA_ON; // Count and start
     }
}
