// ALLISON SOMMERS

// Colors and Offsets
#define COLOR(R, G, B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)

#define SCANLINECOUNTER ((unsigned short *) 0x4000006)
#define OFFSET(r, c, rowlen)  (((r) * (rowlen)) + (c))

/* Button macros */
#define BUTTONS (*(unsigned int *) 0x4000130)
#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)
#define KEY_DOWN_NOW(key) (~(BUTTONS)&key)

// DMA AND MODE VALUES
#define REG_DISPCNT *(unsigned short*) 0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)
#define REG_DMA3SRC *(vu32*)0x40000D4  /* source address*/
#define REG_DMA3DAD *(vu32*)0x40000D8  /* destination address*/
#define REG_DMA3CNT *(vu32*)0x40000DC  /* control register*/
#define DMA_ON (1 << 31)
#define DMA_SOURCE_FIXED (2<<23)


typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef volatile unsigned char  vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int   vu32;

// PROTOTYPES
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawRect3(int r, int c, int width, int height, u16 color);
void delay(int how_long);
void wait_for_vblank();
void blank_screen();
void drawImage3(int r, int c, int width, int height, const u16* image);

// GET VIDEOBUFFER
extern u16 *videoBuffer;
