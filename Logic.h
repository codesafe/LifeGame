#pragma once

#include <stdlib.h>

#define DEAD	0
#define LIVE	1

#define ORIGIN	0
#define TARGET	1

class Logic
{
private:
	unsigned char* buffer[2];
	int* surface;


public:
	Logic();
	~Logic();

	void initlogic();
	void stepsimul();
	void swap();

	int* getbuffer();
	unsigned char getPixel(int x, int y);
	void drawPixel(int x, int y, int value);

	int getliveneighborcount(int x, int y);
	void placeTreasure();

};