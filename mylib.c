#include "mylib.h"
unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int col, int row, volatile unsigned short color){
	videoBuffer[OFFSET(row, col, 240)] = color;
}
void dmaSetPixel(int c, int r, int rowLen){
	DMA[3].dst = &videoBuffer[OFFSET(r,c,rowLen)];
}

void drawRect(int c, int r, int width, int height, u16 color){
	int row;
	for(row=0; row<height; row++){
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(r+row, c, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}	
}

void drawHollowRect(int c, int r, int width, int height, u16 color){
	int other_r = r+height;
	int other_c = c+width;
	/*draw horizontal lines*/
	for(int x = c; x<= other_c; x++){
		setPixel(x,r,color);
		setPixel(x,other_r,color);
	}
	/*draw vertical lines*/
	for(int y = r; y<=other_r;y++){
		setPixel(c,y,color);
		setPixel(other_c,y,color);
	}
}

void plotLine(int c0, int r0, int c1, int r1, u16 color){
	int dx = (c1-c0), sx = c0<c1 ? 1 : -1;
  	if(dx < 0){
  		dx = ~dx + 1;
  	}
  	int dy = (r1-r0), sy = r0<r1 ? 1 : -1; 
  	if(dy < 0){
  		dy = ~dy + 1;
  	}
  	int slope = (dx>dy ? dx : -dy)>>1, s2;
  	for(;;){
    	setPixel(c0,r0,color);
    	if (r0==r1 && c0==c1) break;
    	s2 = slope;
    	if (s2 >-dx) { slope -= dy; c0 += sx; }
    	if (s2 < dy) { slope += dx; r0 += sy; }
  	}
}
int calculateXPosition(int velocity, int c, int r){
	int x = c + velocity;
	return x;

}
int calculateYPosition(int velocity, int c, int r){
	int y = r + velocity;
	return y;
}
void drawCharacter(PLAYER* b){
	drawRect(b->c,b->r,b->width,b->height,b->color);
}

void waitForVBlank(){
	while(SCANLINECOUNTER>160);
	while(SCANLINECOUNTER<160);
}

bool isCollision(PLAYER* a, PLAYER* b){

	int aXCollision = a->c + a->width;
	int aYCollision = a->r + a->height;
	int bXCollision = b->c + b->width;
	int bYCollision = b->r + b->height;
	if(aXCollision >= b->c && aYCollision >= b->r && (a->c < bXCollision) && (a->r <= bYCollision)){
		return true;
	} else {
		return false;
	}
}
bool isPunched(PLAYER* a, PLAYER* b){
	int punch = a->c + a->width + a->armLength;
	if(punch >= b->c && punch <= (b->c + b->width)){
		return true;
	} else {
		return false;
	}
}
void fillScreen(volatile unsigned short color){
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400|DMA_ON|DMA_SOURCE_FIXED;
}
void drawImage3(int c, int r, int width, int height, const u16 image[]){
	for(int i = 0; i < height; i++){
		DMA[3].src = &image[width*i];
		DMA[3].dst = &videoBuffer[OFFSET(i+r,c,240)];//i*240+c
		DMA[3].cnt = width|DMA_ON;
	}
}
void drawBG(const u16 image[]){
	// for (int i = 0; i < 160; i++){+
		DMA[3].src = &image[240];
		DMA[3].dst = &videoBuffer[240];
		DMA[3].cnt = 240|DMA_ON|DMA_SOURCE_FIXED;
	// }
		
}
