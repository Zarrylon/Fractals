#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdio.h>

#include "../lib/graphics.h"
#pragma comment(lib, "lib/graphics.lib")

using std::cout;
using std::cin;
using std::endl;


void getGraph()
{
	int gd = DETECT, gm;
	char pathtodriver[] = "";
	initgraph(&gd, &gm, pathtodriver);
}

void drawLine(int x1, int y1, int x2, int y2, int color)
{
	float dx = abs(x2 - x1);
	float dy = abs(y2 - y1);

	float sx = x1 < x2 ? 1 : -1;
	float sy = y1 < y2 ? 1 : -1;

	float error = dx - dy;

	putpixel(x2, y2, color);

	while (x1 != x2 || y1 != y2)
	{
		putpixel(x1, y1, color);
		float error2 = error * 2;

		if (error2 > -dy)
		{
			error -= dy;
			x1 += sx;
		}
		if (error2 < dx)
		{
			error += dx;
			y1 += sy;
		}
	}
}

void drawKochCurve(int order, int xs, int ys, int xe, int ye, int color)
{
	if (order == 0)
	{
		drawLine(xs, ys, xe, ye, color);
	}
	else
	{
		int dx = (xe - xs) / 3;
		int dy = (ye - ys) / 3;

		int x2 = xs + dx;
		int y2 = ys + dy;

		int x3 = (int)(0.5 * (xs + xe) + sqrt(3) * (ys - ye) / 6);
		int y3 = (int)(0.5 * (ys + ye) + sqrt(3) * (xe - xs) / 6);

		int x4 = 2 * dx + xs;
		int y4 = 2 * dy + ys;

		order--;
		drawKochCurve(order, xs, ys, x2, y2, color);
		drawKochCurve(order, x2, y2, x3, y3, color);
		drawKochCurve(order, x3, y3, x4, y4, color);
		drawKochCurve(order, x4, y4, xe, ye, color);
	}
}

// 640x480
void drawMandelbrotSet(int depth, int color)
{
	float zi, zr, ci, cr, tmp;
	int i, j, k;

	for (i = -320; i < 320; i++)
	{
		ci = (float)(i) / 320.0;

		for (j = -380; j < 160; j++)
		{
			cr = (float)(j) / 240.0;
			zi = 0.0;
			zr = 0.0;

			for (k = 0; k < depth; k++)
			{
				tmp = zr * zr - zi * zi;
				zi = 2 * zr * zi + ci;
				zr = tmp + cr;

				if (zr * zr + zi * zi > 1.0E16) break;
			}
			if (k < depth)
				putpixel(i + 320, j + 380, k % 3 + 1);
			else
				putpixel(i + 320, j + 380, color);
		}

		if (_kbhit()) break;
	}
}

void drawBarnsleyFern(int depth, int color)
{
	srand(time(NULL));

	float x = 0.0;
	float y = 0.0;

	float xn;
	float yn;

	int roll;

	for (int count = 0; count < depth; count++)
	{
		roll = rand() % 100;

		if (roll < 1)
		{
			xn = 0;
			yn = 0.16 * y;
		}
		else if (roll < 8)
		{
			xn = (-0.15 * x) + (0.28 * y);
			yn = (0.26 * x) + (0.24 * y) + 0.44;
		}
		else if (roll < 15)
		{
			xn = (0.2 * x) - (0.26 * y);
			yn = (0.23 * x) + (0.22 * y) + 1.6;
		}
		else
		{
			xn = (0.85 * x) + (0.04 * y);
			yn = (-0.04 * x) + (0.85 * y) + 1.6;
		}

		x = xn;
		y = yn;

		int printX = x * 50 + 320;
		int printY = 480 - (y * 50);

		putpixel(printX, printY, color);

		if (count % 100 == 0)
			delay(1);
	}
}

int main()
{
	int choice, order, depth;

	cout << "1. Koch Curve" << endl << "2. Mandle Set" << endl << "3. Barnsley Fern" << endl << endl;
	cin >> choice;

	system("cls");

	cout << "Order: ";
	cin >> order;

	getGraph();

	if (choice == 1)
	{
		drawKochCurve(order, 150, 20, 20, 280, 7);
		drawKochCurve(order, 280, 280, 150, 20, 8);
		drawKochCurve(order, 20, 280, 280, 280, 15);
		
	}
	else if (choice == 2)
	{
		drawMandelbrotSet(order, 4);
	}
	else if (choice == 3)
	{
		drawBarnsleyFern(order, 2);
	}

	cout << "\n\n[Successfull]";

	_getch();
	closegraph();
}
