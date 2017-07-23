#include "Nest.h"


Nest::Nest()
{
	_x = 0;
	_y = 0;
	_tile = 'N';
	_amountFood = 0;
}


Nest::~Nest()
{
}

//GETTERS
//GETS THE TILE AS THE SYMBOL (LIKE "A")
char Nest::getTile()
{
	return _tile;
}
//GETS THE FOOD IT CARRIES
int Nest::getAmountFood()
{
	return _amountFood;
}

//GETS COORDINATES
//GETS X
int Nest::getX()
{
	return _x;
}
//GETS Y
int Nest::getY()
{
	return _y;
}


//SETTERS

void Nest::setTile(char tile)
{
	_tile = tile;
}

void Nest::addAmountFood(int amountFood)
{
	_amountFood += amountFood;
}


//SETS COORDINATES

void Nest::setX(int x)
{
	_x = x;
}

void Nest::setY(int y)
{
	_y = y;
}

bool Nest::creatAntPossible(int amountFoodNeeded)
{
	if (_amountFood >= amountFoodNeeded)
	{
		return true;
	}
	else
	{
		return false;
	}
}
