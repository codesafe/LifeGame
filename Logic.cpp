#include "Predef.h"
#include "Logic.h"

/*
Any live cell with fewer than two live neighbors dies, as if caused by under-population.
살아있는 셀의 살아있는 이웃셀의 수가 2보다 작으면 해당 셀은 죽는다 (under-population)

Any live cell with two or three live neighbors lives on to the next generation.
살아있는 셀의 살아있는 이웃셀의 수가 2 or 3 이면 해당 셀은 다음세대에 살아 남는다

Any live cell with more than three live neighbors dies, as if by overcrowding.
살아있는 셀의 살아있는 이웃셀의 수가 3보다 크면 해당 셀은 죽는다 (overcrowding)

Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
죽어있는 셀의 살아있는 이웃셀의 수가 3이면 해당셀은 부활한다 
*/

Logic::Logic()
{

}

Logic::~Logic()
{
	delete[] buffer[ORIGIN];
	delete[] buffer[TARGET];
	delete[] surface;
}

void Logic::initlogic()
{
	for (int i = 0; i < 2; i++)
	{
		buffer[i] = new unsigned char[SCREEN_XSIZE * SCREEN_YSIZE];
		memset(buffer[i], DEAD, SCREEN_XSIZE * SCREEN_YSIZE);
	}

	surface = new int[SCREEN_XSIZE * SCREEN_YSIZE * 4];

	for (int y = 0; y < SCREEN_YSIZE; y++)
		for (int x = 0; x < SCREEN_XSIZE; x++)
		{
			int num = rand() % 100;
			if (num < 40)
				drawPixel(x, y, LIVE);
			else
				drawPixel(x, y, DEAD);
		}

	swap();
}

void Logic::stepsimul()
{
#if 1
	// Normal Life Game
	for (int y = 0; y < SCREEN_YSIZE; y++)
	{
		for (int x = 0; x < SCREEN_XSIZE; x++)
		{
			int cell = getPixel(x, y);
			int livecount = getliveneighborcount(x, y);
			if (cell == LIVE)
			{
				if(livecount < 2)
					drawPixel(x, y, DEAD);
				else if (livecount == 2 || livecount == 3)
					drawPixel(x, y, LIVE);
				else if (livecount > 3)
					drawPixel(x, y, DEAD);
			}
			else
			{
				if (livecount == 3)
				{
					drawPixel(x, y, LIVE);
				}
			}
		}
	}
#else
	int birthlimit = 4;
	int deathlimit = 3;

	for (int y = 0; y < SCREEN_YSIZE; y++)
	{
		for (int x = 0; x < SCREEN_XSIZE; x++)
		{
			int cell = getPixel(x, y);
			int livecount = getliveneighborcount(x, y);
			if (cell == LIVE)
			{
				if (livecount < deathlimit)
					drawPixel(x, y, DEAD);
				else 
					drawPixel(x, y, LIVE);
			}
			else
			{
				if (livecount > birthlimit)
					drawPixel(x, y, LIVE);
				else
					drawPixel(x, y, DEAD);
			}
		}
	}
#endif
	swap();
}

// 8 방향
int Logic::getliveneighborcount(int x, int y)
{
	int xDir[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int yDir[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int count = 0;

	for (int i = 0; i < 8; i++)
	{
		int newx = x + xDir[i];
		int newy = y + yDir[i];

		if (newx < 0 || newy < 0 || newx >= SCREEN_XSIZE || newy >= SCREEN_YSIZE)
		{
			//count++;
			continue;
		}

		if (getPixel(newx, newy) == LIVE)
			count++;
	}

	return count;
}

void Logic::placeTreasure()
{
	memcpy(buffer[TARGET], buffer[ORIGIN], SCREEN_XSIZE * SCREEN_YSIZE);

	int treasureHiddenLimit = 5;
	for (int y = 0; y < SCREEN_YSIZE; y++)
	{
		for (int x = 0; x < SCREEN_XSIZE; x++)
		{
			if (getPixel(x,y) == DEAD) 
			{
				int nbs = getliveneighborcount(x, y);
				if (nbs >= treasureHiddenLimit) 
				{
					drawPixel(x, y, 2);
				}
			}
		}
	}

	swap();
}


int* Logic::getbuffer()
{
	for (int y = 0; y < SCREEN_YSIZE; y++)
	{
		for (int x = 0; x < SCREEN_XSIZE; x++)
		{
			unsigned char v = getPixel(x, y);
			int color = 0;
			if (v == DEAD)
				color = 0;
			else if (v == LIVE)
				color = 0xFFFFFFFF;
			else
				color = 0x00FFFFFF;
			surface[y * SCREEN_XSIZE + x] = color;
		}
	}

	return surface;
}

unsigned char Logic::getPixel(int x, int y)
{
	unsigned char* ptr = buffer[ORIGIN];
	return ptr[y * SCREEN_XSIZE + x];
}

void Logic::drawPixel(int x, int y, int value)
{
	unsigned char* ptr = buffer[TARGET];
	ptr[y * SCREEN_XSIZE + x] = value;
}


void Logic::swap()
{
	// Targe -> Origin
	memcpy(buffer[ORIGIN], buffer[TARGET], SCREEN_XSIZE * SCREEN_YSIZE);
}