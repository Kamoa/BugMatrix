#include <algorithm>

class organism
{
public:
	organism() {}
	virtual void move(int x, int y, organism(&p_grid)[20][20]) {}//location parameters
	virtual void breed(int x, int y, organism(&p_grid)[20][20]) {}//
protected:
	int stepCount;
	int x_loc;
	int y_loc;
};
class ant : public organism
{
public:
	ant() : organism() { stepCount = 0; }
	ant(int x, int y) : organism() { stepCount = 0; x_loc = x; y_loc = y;	}
	void move(int x, int y, organism(&p_grid)[20][20]);
	void breed(int x, int y, organism(&p_grid)[20][20]);
};
class doodlebug : public organism
{
private:
	int daysSinceAnt;
public: 
	doodlebug() : organism() { stepCount, daysSinceAnt = 0; }
	doodlebug(int x, int y) :organism() {stepCount = 0; daysSinceAnt = 0; x_loc = x; y_loc = y;}
	void move(int x, int y, organism(&p_grid)[20][20]);
	void breed(int x, int y, organism(&p_grid)[20][20]);
	void starve(organism(&p_grid)[20][20]);

};

void ant::move(int x, int y, organism(&p_grid)[20][20])
{
	int directionLR = rand() % 2;
	int directionUD = rand() % 2;
	if (directionUD == 0)
	{
		if (directionLR == 0)
		{
			if (x - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x - 1][y]))//checks if possible to move to
				x_loc = x - 1;
			else
				directionLR = 1;//changes destination if couldn't move
		}
		if (directionLR == 1)
		{
			if (x + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x + 1][y]))
				x_loc = x + 1;
			else
				directionUD == 1;
		}
	}
	if (directionUD == 1)
	{
		if (directionLR == 0)
		{
			if (y - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x][y - 1]))
				y_loc = y - 1;
			else
				directionLR = 1;
		}
		if (directionLR == 1)
		{
			if (y + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x][y + 1]))
				x_loc = y + 1;
		}
	}
	std::swap(p_grid[x][y], p_grid[x_loc][y_loc]);
	stepCount++;
	if (stepCount >= 3)
		breed(x_loc, y_loc, p_grid);
}
void doodlebug::move(int x, int y, organism(&p_grid)[20][20])
{
	daysSinceAnt++;
	int directionLR = rand() % 2;
	int directionUD = rand() % 2;
	if (directionUD == 0)
	{
		if (directionLR == 0)
		{
			if (x - 1 >= 0 && !dynamic_cast<doodlebug*>(&p_grid[x - 1][y]))//checks if possible to move to
			{
				if (dynamic_cast<ant*>(&p_grid[x - 1][y]))
					daysSinceAnt = 0;//resets the days since eaten an ant if an ant was eaten
				x_loc = x - 1;
			}
			else
				directionLR = 1;//changes destination if couldn't move
		}
		if (directionLR == 1)
		{
			if (x + 1 <= 19 && !dynamic_cast<doodlebug*>(&p_grid[x + 1][y]))
			{
				if (dynamic_cast<ant*>(&p_grid[x + 1][y]))
					daysSinceAnt = 0;
				x_loc = x + 1;
			}
			else
				directionUD == 1;
		}
	}
	if (directionUD == 1)
	{
		if (directionLR == 0)
		{
			if (y - 1 >= 0 && !dynamic_cast<doodlebug*>(&p_grid[x][y - 1]))
			{
				if (dynamic_cast<ant*>(&p_grid[x][y-1]))
					daysSinceAnt = 0;
				y_loc = y - 1;
			}
			else
				directionLR = 1;
		}
		if (directionLR == 1)
		{
			if (y + 1 <= 19 && !dynamic_cast<doodlebug*>(&p_grid[x][y + 1]))
			{
				if (dynamic_cast<ant*>(&p_grid[x][y+1]))
					daysSinceAnt = 0;
				x_loc = y + 1;
			}
		}
	}
	p_grid[x_loc][y_loc] = p_grid[x][y];
	delete[x] (p_grid)[y];
	stepCount++;
	if (stepCount >= 8)
		breed(x_loc, y_loc, p_grid);
	if (daysSinceAnt > 3)
		starve(p_grid);
}

void ant::breed(int x, int y, organism(&p_grid)[20][20])
{
	ant a;
	a.x_loc = x;//temporarily ants are at "same spot"
	a.y_loc = y;
	int directionLR = rand() % 2;
	int directionUD = rand() % 2;
	if (directionUD == 0)
	{
		if (directionLR == 0)
		{
			if (x - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x - 1][y]))//checks if possible to move to
			{
				a.x_loc = x - 1;
			}
			else
				directionLR = 1;//changes destination if couldn't move
		}
		if (directionLR == 1)
		{
			if (x + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x + 1][y]))
				a.x_loc = x + 1;
			else
				directionUD == 1;
		}
	}
	if (directionUD == 1)
	{
		if (directionLR == 0)
		{
			if (y - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x][y - 1]))
				a.y_loc = y - 1;
			else
				directionLR = 1;
		}
		if (directionLR == 1)
		{
			if (y + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x][y + 1]))
				a.x_loc = y + 1;
		}
	}
	p_grid[a.x_loc][a.y_loc] = a;//moves the new ant to the designated spot
	delete[x](p_grid)[y];
}

void doodlebug::breed(int x, int y, organism(&p_grid)[20][20])
{
	doodlebug a;
	a.x_loc = x;//temporarily doodlebugs are at "same spot"
	a.y_loc = y;
	int directionLR = rand() % 2;
	int directionUD = rand() % 2;
	if (directionUD == 0)
	{
		if (directionLR == 0)
		{
			if (x - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x - 1][y]))//checks if possible to move to
				a.x_loc = x - 1;
			else
				directionLR = 1;//changes destination if couldn't move
		}
		if (directionLR == 1)
		{
			if (x + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x + 1][y]))
				a.x_loc = x + 1;
			else
				directionUD == 1;
		}
	}
	if (directionUD == 1)
	{
		if (directionLR == 0)
		{
			if (y - 1 >= 0 && !dynamic_cast<organism*>(&p_grid[x][y - 1]))
				a.y_loc = y - 1;
			else
				directionLR = 1;
		}
		if (directionLR == 1)
		{
			if (y + 1 <= 19 && !dynamic_cast<organism*>(&p_grid[x][y + 1]))
				a.x_loc = y + 1;
		}
	}
	p_grid[a.x_loc][a.y_loc] = a;//moves the new doodlebug to the designated spot
	delete[x](p_grid)[y];
}

void doodlebug::starve(organism(&p_grid)[20][20])
{
	delete[x_loc] (p_grid)[y_loc];
}