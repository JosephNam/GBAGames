#include <stdbool.h>
extern unsigned short *videoBuffer;
#define OFFSET(r,c,rowlen) ((r)*(rowlen)+(c))
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define REG_DISPCTL *(u16 *)0x4000000
#define RGB(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define LIGHTBLUE RGB(13,31,31)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,16,16)
#define DARKGREEN RGB(0,8,4)
#define ORANGE RGB(31,8,0)
#define WHITE RGB(31,31,31)
#define GOLD RGB(29,29,0)
#define BLACK RGB(0,0,0)
#define BUTTON_ADDRESS *(volatile unsigned short*) 0x4000130
#define BUTTON_DOWN_NOW(key) (~BUTTON_ADDRESS & (key))
#define SCANLINECOUNTER *(volatile unsigned short*) 0x4000006
#define BUTTON_A 1
#define BUTTON_B (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START (1<<3)
#define BUTTON_RIGHT (1<<4)
#define BUTTON_LEFT (1<<5)
#define BUTTON_UP (1<<6)
#define BUTTON_DOWN (1<<7)
#define BUTTON_R (1<<8)
#define BUTTON_L (1<<9)
/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

typedef unsigned short u16;
typedef unsigned int u32;
//direction convention 0 means left 1 means right
typedef struct {
	int c;
	int r;
	int width;
	int height;
	int oldc;
	int oldr;
	int fc;
	int fr;
	int direction;
	int health;
	int armLength;
	int armWidth;
	u16 color;
} PLAYER;
void drawCharacter(PLAYER* b);
bool isCollision(PLAYER* a, PLAYER*b);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void drawHollowRect(int c, int r, int width, int height, u16 color);
void drawRect(int c, int r, int width, int height, u16 color);
void setPixel(int c, int r, u16 color);
void waitForVBlank(void);
void fillScreen(volatile unsigned short color);
int calculateXPosition(int velocity, int c, int r);
int calculateYPosition(int velocity, int c, int r);
void drawImage3(int r, int c, int width, int height, const u16* image);
bool isPunched(PLAYER* a, PLAYER* b);