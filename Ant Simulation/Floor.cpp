#include "Floor.h"
#include <random>
#include <time.h>

//CONSTRUCTOR
Floor::Floor()
{
	//SETS THE PROPERTIES TO DEFAULT
	_tile = '.';
	_hasFood = false;
	_pheromones = 0.0;

	//SETS THE FOOD TO TRUE IF SUCCESS AND THE AMOUNT OF FOOD ON THE FLOOR
	if (dice(1, 100) > 97)
	{
		_tile = 'F';
		_hasFood = true;
		_amountFood = dice(500, 1000);
	}
}

//DESTRUCTOR
Floor::~Floor()
{
}

//GETTERS
//GETS THE SYMBOL OF THE FLOOR
char Floor::getTile()
{
	return _tile;
}
//GETS IF THE FLOOR HAS FOOD OR NOT
bool Floor::getFood()
{
	return _hasFood;
}
//GETS THE AMOUNT OF FOOD ON THIS FLOOR TILE
int Floor::getAmountFood()
{
	return _amountFood;
}
//GETS THE AMOUNT OF PHEREOMONES
float Floor::getPheromones()
{
	return _pheromones;
}

//SETTERS
//SETS THE TILE (FOR EXAMPLE TO ".")
void Floor::setTile(char tile)
{
	_tile = tile;
}
//BOOLEN IF THE FLOOR HAS FOOD
void Floor::setFood(bool hasFood)
{
	_hasFood = hasFood;
}

//ADDS FOOD
void Floor::addFood(int amountFood)
{
	_amountFood += amountFood;
}

//ADDS PHEROMONES
void Floor::addPheromones(float addpheromones)
{
	_pheromones += addpheromones;
}

//SETS THE PHEROMONES
void Floor::updatePheromones(float evaporation)
{
	_pheromones = (1 - evaporation) * _pheromones;

	if (_pheromones < 0.5)
	{
		_pheromones = 0;
	}
}

//Random Engine
int Floor::dice(int min, int max)
{
	static std::mt19937 generator((unsigned int)time(NULL));
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
