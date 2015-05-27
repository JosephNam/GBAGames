#include "text.h"
#include "mylib.h"
void drawChar(int col, int row, char ch, unsigned short color)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{

				setPixel(col+c, row+r, color);
			}
		}
	}
}

void drawString(int col, int row, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(col, row, *str++, color);
		col +=6;

	}
}