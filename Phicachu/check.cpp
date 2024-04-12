#include "check.h"
#include "utility.h"

bool checkChuI(tile** table, int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		int step;
		if (y1 < y2)
			step = 1;
		else
			step = -1;

		while (y1 != y2)
		{
			y1 += step;
			if (table[y1][x1].empty == false && y1 != y2)
			{
				return false;
			}
		}
		return true;
	}

	if (y1 == y2)
	{
		int step;
		if (x1 < x2)
			step = 1;
		else
			step = -1;

		while (x1 != x2)
		{
			x1 += step;
			if (table[y1][x1].empty == false && x1 != x2)
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

bool checkChuL(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp)
{
	if (checkChuI(table, x1, y1, x2, y1) && checkChuI(table, x2, y1, x2, y2) && table[y1][x2].empty)
	{
		xtemp = x2;
		ytemp = y1;
		return true;
	}
	if (checkChuI(table, x1, y1, x1, y2) && checkChuI(table, x1, y2, x2, y2) && table[y2][x1].empty)
	{
		xtemp = x1;
		ytemp = y2;
		return true;
	}
	return false;
}

bool checkChuUZ(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp, int& xtemp2, int& ytemp2, int xmax, int ymax)
{
	xtemp2 = x1;
	ytemp2 = y1;
	while (xtemp2 < xmax + 1)
	{
		xtemp2++;
		if (!table[ytemp2][xtemp2].empty)
			break;
		else
			if (checkChuL(table, xtemp2, ytemp2, x2, y2, xtemp, ytemp))
				return true;
	}
	xtemp2 = x1;
	while (xtemp2 > 0)
	{
		xtemp2--;
		if (!table[ytemp2][xtemp2].empty)
			break;
		else
			if (checkChuL(table, xtemp2, ytemp2, x2, y2, xtemp, ytemp))
				return true;
	}
	xtemp2 = x1;
	while (ytemp2 > 0)
	{
		ytemp2--;
		if (!table[ytemp2][xtemp2].empty)
			break;
		else
			if (checkChuL(table, xtemp2, ytemp2, x2, y2, xtemp, ytemp))
				return true;
	}
	ytemp2 = y1;
	while (ytemp2 < ymax + 1)
	{
		ytemp2++;
		if (!table[ytemp2][xtemp2].empty)
			break;
		else
			if (checkChuL(table, xtemp2, ytemp2, x2, y2, xtemp, ytemp))
				return true;
	}
	return false;
}

int checkAll(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp, int& xtemp2, int& ytemp2, int xmax, int ymax)
{
	if (checkChuI(table, x1, y1, x2, y2))
		return 1;
	else if (checkChuL(table, x1, y1, x2, y2, xtemp, ytemp))
		return 2;
	else if (checkChuUZ(table, x1, y1, x2, y2, xtemp, ytemp, xtemp2, ytemp2, xmax, ymax))
		return 3;
	return 0;
}

bool checkAvailablePair(tile** table, int xmax, int ymax, int & x1, int & y1, int & x2, int & y2)
{
	int temp1, temp2, temp3, temp4;
	for (int i = 1; i < ymax + 1; i++)
	{
		for (int j = 1; j < xmax + 1; j++)
		{
			if (!table[i][j].empty)
			{
				x1 = j;
				y1 = i;
				for (int k = i; k < ymax + 1; k++)
				{
					for (int l = 1; l < xmax + 1; l++)
					{
						if (!table[k][l].empty && (i!= k || j != l) && table[i][j].pokemon == table[k][l].pokemon && checkAll(table, j, i, l, k, temp1, temp2, temp3, temp4, xmax, ymax))
						{
							x2 = l;
							y2 = k;
							//std::cout << "x: " << j << " y: " << i  << "    x2: " << l  << " y2: " << k << " " << " check: " << checkAll(table, j, i, l, k, temp1, temp2, temp3, temp4, xmax, ymax);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}