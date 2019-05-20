#include <iostream>
#include <iomanip>
#include "bugs.h"
using namespace std;



int main()
{
	organism grid[20][20]; // creategrid

	for (int i = 0; i < 20; i++)
	{
		for (int k = 0; k < 20; k++)
		{
			if (i % 2 == 0 && k%2 == 0)
			{
				ant a(i, k);//populate 2d array with 100 ants spread evenly
				grid[i][k] = a;
			}
		}
	}
	grid[1][0] = doodlebug(1, 0);//put in 5 doodlebugs
	grid[3][5] = doodlebug(3, 5);
	grid[5][15] = doodlebug(5, 15);
	grid[8][5] = doodlebug(8, 5);
	grid[17][12] = doodlebug(17, 12);

	for (int i = 0; i < 20; i++)//displayer
	{
		for (int k = 0; k < 20; k++)
		{
			if (dynamic_cast<doodlebug*>(&grid[i][k]))
			{
				cout << setw(3) << "X ";
			}
			else if (dynamic_cast<ant*>(&grid[i][k]))
			{
				cout << setw(3) << "O ";
			}
			else
				cout << setw(3) << "- ";
		}
		cout << endl;
	}

	return 0;
}