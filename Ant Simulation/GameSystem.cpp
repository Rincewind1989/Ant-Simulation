#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "GameSystem.h"


//Constructor
GameSystem::GameSystem(int numAnts, int amountFood, int worldWidth, int worldHeight, int amountFoodNeeded, float evaporation)
{
	//Creates the world
	_worldHeight = worldHeight;
	_worldWidth = worldWidth;

	_amountFoodNeeded = amountFoodNeeded;
	_evaporation = evaporation;

	//Initializing the Textures and Sprites
	//Grass Texture
	sf::Texture grass;
	grass.loadFromFile("Textures/grass.jpg");
	_textures.push_back(grass);

	//Grass Sprite
	_grassSprite.setTexture(_textures.back());
	_grassSprite.setScale(sf::Vector2f((1.0f / _textures.back().getSize().x) * (worldWidth / 10.0f),( 1.0f / _textures.back().getSize().y) * (worldHeight / 10.0f)));
	
	//Ant Texture
	sf::Texture ant;
	ant.loadFromFile("Textures/ant.png");
	_textures.push_back(ant);

	//Ant Sprite
	_antSprite.setTexture(_textures.back());
	_antSprite.setScale(sf::Vector2f((1.0f / _textures.back().getSize().x) * (worldWidth / 10.0f), (1.0f / _textures.back().getSize().y) * (worldHeight / 10.0f)));
	
	//Apple Texture
	sf::Texture apple;
	apple.loadFromFile("Textures/apple.png");
	_textures.push_back(apple);

	//Apple Sprite
	_appleSprite.setTexture(_textures.back());
	_appleSprite.setScale(sf::Vector2f((1.0f / _textures.back().getSize().x) * (worldWidth / 10.0f), (1.0f / _textures.back().getSize().y) * (worldHeight / 10.0f)));

	//Hole Texture
	sf::Texture hole;
	hole.loadFromFile("Textures/hole.png");
	_textures.push_back(hole);

	//Hole Sprite
	_holeSprite.setTexture(_textures.back());
	_holeSprite.setScale(sf::Vector2f((1.0f / _textures.back().getSize().x) * (worldWidth / 10.0f), (1.0f / _textures.back().getSize().y) * (worldHeight / 10.0f)));

	//Creates ants
	for (int i = 0; i < numAnts; i++)
	{
		Ant tmp;
		_ants.push_back(tmp);
		_ants[i].setX(int(worldWidth / 2));
		_ants[i].setY(int(worldHeight / 2));
	}

	//Creates nest
	_nest.setX(int(worldWidth / 2));
	_nest.setY(int(worldHeight / 2));
	_nest.addAmountFood(amountFood);

	//Sets controler Position
	_controler.setXY(int(worldWidth)/4, int(worldHeight) / 4);

	//Creates food and floor
	for (int tmpY = 0; tmpY < worldHeight; tmpY++)
	{
		std::vector <Floor> tmp;
		_gameVector.push_back(tmp);
		for (int tmpX = 0; tmpX < worldWidth; tmpX++)
		{
			Floor tmp2;
			_gameVector[tmpY].push_back(tmp2);
		}
	}
}

//Destructor
GameSystem::~GameSystem()
{
}

//Function to create an ant
void GameSystem::createAnt()
{
	if (_nest.creatAntPossible(_amountFoodNeeded))
	{
		Ant tmp;
		_ants.push_back(tmp);
		_ants[_ants.size() - 1].setX(int(_worldWidth / 2));
		_ants[_ants.size() - 1].setY(int(_worldHeight / 2));
		_nest.addAmountFood(-1 * (_amountFoodNeeded));
	}
}

//Displays the map
void GameSystem::printWorld(sf::RenderWindow &window)
{
	//Prints every sprite
	for (int tmpY = 0 + _controler.getY(); tmpY < _gameVector.size(); tmpY++)
	{
		for (int tmpX = 0 + _controler.getX(); tmpX < _gameVector[tmpY].size(); tmpX++)
		{																				
				_grassSprite.setPosition(sf::Vector2f((tmpX - _controler.getX()) * _worldWidth / 10.0f, (tmpY - _controler.getY()) * _worldHeight / 10.0f));
				window.draw(_grassSprite);
				
				//Prints the nest
				if (_nest.getX() == tmpX && _nest.getY() == tmpY)
				{
					_holeSprite.setPosition(sf::Vector2f((tmpX - _controler.getX()) * _worldWidth / 10.0f, (tmpY - _controler.getY()) * _worldHeight / 10.0f));
					window.draw(_holeSprite);
				}

				//Sees if there is food on the tile
				if (_gameVector[tmpY][tmpX].getFood())
				{
					_appleSprite.setPosition(sf::Vector2f((tmpX - _controler.getX()) * _worldWidth / 10.0f, (tmpY - _controler.getY()) * _worldHeight / 10.0f));
					window.draw(_appleSprite);
				}

				//For all ants
				for (unsigned int ant = 0; ant < _ants.size(); ant++)
				{

					//SEES IF AN ANT IS ON THE TILE
					if (_ants[ant].getX() == tmpX && _ants[ant].getY() == tmpY)
					{
						_antSprite.setPosition(sf::Vector2f((tmpX - _controler.getX()) * _worldWidth / 10.0f, (tmpY - _controler.getY()) * _worldHeight / 10.0f));
						window.draw(_antSprite);
						break;
					}

				}
		}
	}
}


//Text Color
void GameSystem::setColor(int value)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (WORD)value);
}

//Console Pointer Position
void GameSystem::gotoxy(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p1;

	p1.X = x;
	p1.Y = y;

	SetConsoleCursorPosition(console, p1);
}

//Random Engine for integer roll
int GameSystem::dice(int min, int max)
{
	static std::mt19937 generator((unsigned int)time(NULL));
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

//Food detection function
void GameSystem::foodDetection(int ant)
{
	//LOOKS FOR FOOD NEARBY
	//LOOP FOR Y-AXIS
	for (int tmpY = -1 * (_ants[ant].getFoodDetectionRange()); tmpY < _ants[ant].getFoodDetectionRange(); tmpY++)
	{
		//LOOP FOR X-AXIS
		for (int tmpX = -1 * (_ants[ant].getFoodDetectionRange()); tmpX < _ants[ant].getFoodDetectionRange(); tmpX++)
		{

			if (_gameVector[_ants[ant].getY() + tmpY][_ants[ant].getX() + tmpX].getFood())
			{
				_ants[ant].setState(1);
				_ants[ant].setFoodX(_ants[ant].getX() + tmpX);
				_ants[ant].setFoodY(_ants[ant].getY() + tmpY);
			}
		}
	}
}

//Lays down pheromones for the ant
void GameSystem::layPheromones(float pheromones, int ant)
{
	//LEAVES PHEROMONES FOR OTHER ANTS TO FIND FOOD
	for (int tmpY = -2; tmpY <= 2; tmpY++)
	{
		for (int tmpX = -2; tmpX <= 2; tmpX++)
		{
			if ((tmpX + _ants[ant].getX()) > 0 && (tmpX + _ants[ant].getX()) < _gameVector[0].size() && (tmpY + _ants[ant].getY()) > 0 && (tmpY + _ants[ant].getY()) < _gameVector.size())
			{
				if (tmpX == 0 && tmpY == 0)
				{
					_gameVector[_ants[ant].getY() + tmpY][_ants[ant].getX() + tmpX].addPheromones(pheromones);
				}
				else if (abs(tmpX) + abs(tmpY) <= 2 && !(tmpX == 0 && tmpY == 0))
				{
					_gameVector[_ants[ant].getY() + tmpY][_ants[ant].getX() + tmpX].addPheromones(pheromones / 3);
				}
				else
				{
					_gameVector[_ants[ant].getY() + tmpY][_ants[ant].getX() + tmpX].addPheromones(pheromones / 9);
				}
			}
		}
	}
}

//Wald to the food function
void GameSystem::walkToFood(int ant)
{
	//Sets the distance bewteen position and nest to calculate the pheromones used
	float distanceSquare = pow((_ants[ant].getY() - _nest.getY()), 2.0f) + pow((_ants[ant].getX() - _nest.getX()), 2.0f);
	float distance = sqrt(distanceSquare);
	float multiplier = pow(1.25, distance);

	//Leaves pheromones for other ants
	layPheromones(50.0f * multiplier, ant);

	//Walfs toward the food in x_axis
	if (_ants[ant].getFoodX() - _ants[ant].getX() < 0)
	{
		_ants[ant].setX(_ants[ant].getX() - 1);
	}
	else if (_ants[ant].getFoodX() - _ants[ant].getX() > 0)
	{
		_ants[ant].setX(_ants[ant].getX() + 1);
	}
	else
	{
		//wait for x-axis to reach
	}
	//Walks toward the y-axis
	if (_ants[ant].getFoodY() - _ants[ant].getY() < 0)
	{
		_ants[ant].setY(_ants[ant].getY() - 1);
	}
	else if (_ants[ant].getFoodY() - _ants[ant].getY() > 0)
	{
		_ants[ant].setY(_ants[ant].getY() + 1);
	}
	else
	{
		//Collect food
		if (_ants[ant].getFoodX() - _ants[ant].getX() == 0)
		{
			//Sets the state of the ant (SHOULD BE AN ENUM)
			_ants[ant].setState(2);

			//Adds food to the inventory of the ant
			_gameVector[_ants[ant].getY()][_ants[ant].getX()].addFood(-_ants[ant].getFoodThatCanBeCarried());
			_ants[ant].setFoodCarrying(_ants[ant].getFoodThatCanBeCarried());

			//Deletes the food on the floor if empty
			if (_gameVector[_ants[ant].getY()][_ants[ant].getX()].getAmountFood() <= 0)
			{
				_gameVector[_ants[ant].getY()][_ants[ant].getX()].setFood(false);
				_gameVector[_ants[ant].getY()][_ants[ant].getX()].setTile('.');
			}
		}
	}
}

//Walk to the nest function
void GameSystem::walkToNest(int ant)
{

	//Sets the distance bewteen position and nest to calculate the pheromones used
	float distanceSquare = pow((_ants[ant].getY() - _nest.getY()), 2.0f) + pow((_ants[ant].getX() - _nest.getX()), 2.0f);
	float distance = sqrt(distanceSquare);
	float multiplier = pow(1.25, distance);

	//Leaves pheromones for other ants
	layPheromones(10.0f * multiplier, ant);

	//WALKS TOWARDS THE NEST IN X-AXIS
	if (_nest.getX() - _ants[ant].getX() < 0)
	{
		_ants[ant].setX(_ants[ant].getX() - 1);
	}
	else if (_nest.getX() - _ants[ant].getX() > 0)
	{
		_ants[ant].setX(_ants[ant].getX() + 1);
	}
	else
	{
		//WAIT FOR Y-AXIS TO REACH
	}
	//WALKS TOWARDS THE FOOD IN Y-AXIS
	if (_nest.getY() - _ants[ant].getY() < 0)
	{
		_ants[ant].setY(_ants[ant].getY() - 1);
	}
	else if (_nest.getY() - _ants[ant].getY() > 0)
	{
		_ants[ant].setY(_ants[ant].getY() + 1);
	}
	else
	{
		//Depositing food
		if (_nest.getX() - _ants[ant].getX() == 0)
		{
			_ants[ant].setState(0);
			_nest.addAmountFood(_ants[ant].getFoodCarrying());
			_ants[ant].setFoodCarrying(0);
		}
	}
}

//Takes out one target out of the possible pheromone vector
void GameSystem::findTargetTile(int ant)
{
	float randomNumber = dice(0, 999) / 1000.0f;
	float sumOfPheromones = 0;

	int targetX = 0;
	int targetY = 0;

	for (int tmp3 = 0; tmp3 < 9; tmp3++)
	{
		sumOfPheromones += _ants[ant].getPheromoneTarget(tmp3).getPheromones();
		if (randomNumber <= sumOfPheromones)
		{
			targetX = _ants[ant].getPheromoneTarget(tmp3).getX();
			targetY = _ants[ant].getPheromoneTarget(tmp3).getY();
			break;
		}
	}

	_ants[ant].setMemory(_ants[ant].getX() - targetX, (_ants[ant].getY() - targetY));
	_ants[ant].setX(targetX);
	_ants[ant].setY(targetY);
}

//Updating the movement if no food detected or ant has no food
void GameSystem::udpateMovement(int ant)
{
	//Detects pheromones and randomly chooses one out of the target tiles depending on the pheromones on the tiles
	if (detectPheromones(ant) && _ants[ant].getTimeUntilPheromoneDetection() == 0)
	{
		_ants[ant].setTimeUntilRandomWalk(_ants[ant].getTimeUntilRandomWalk() - 1);
		findTargetTile(ant);
		if (_ants[ant].getTimeUntilRandomWalk() == 0)
		{
			_ants[ant].setTimeUntilPheromoneDetection(dice(3, 8));
		}
	}
	//Random walk if no pheromones
	else
	{
		_ants[ant].setTimeUntilPheromoneDetection(_ants[ant].getTimeUntilPheromoneDetection() - 1);
		randomWalk(ant);
		if (_ants[ant].getTimeUntilPheromoneDetection() == 0)
		{
			_ants[ant].setTimeUntilRandomWalk(dice(4, 8));
		}
	}
}

//Detects pheromones nearby and returns true if there are any
bool GameSystem::detectPheromones(int ant)
{
	//FIRST WITHOUT ANY MEMORYFUNCTION, SHOULD LATER BE IMPLEMENTED (TODO!)

	float pheromones_sum = 0;
	//Sums up all pheromones
	for (int tmpY = -1 ; tmpY <= 1 ; tmpY++)
	{
		for (int tmpX = -1 ; tmpX <= 1 ; tmpX++)
		{
			if ((tmpX + _ants[ant].getX()) > 0 && (tmpX + _ants[ant].getX()) < _gameVector[0].size() && (tmpY + _ants[ant].getY()) > 0 && (tmpY + _ants[ant].getY()) < _gameVector.size())
			{
				pheromones_sum += _gameVector[tmpY + _ants[ant].getY()][tmpX + _ants[ant].getX()].getPheromones();
			}
		}
	}

	//Weights the pheromones for every tile and puts it into a private vector for the ant
	if (pheromones_sum != 0)
	{
		float weightedPheromones = 0;
		int tmp = 0;
		for (int tmpY = -1; tmpY <= 1 ; tmpY++)
		{
			for (int tmpX = -1; tmpX <= 1; tmpX++)
			{
				weightedPheromones = _gameVector[_ants[ant].getY() + tmpY][_ants[ant].getX() + tmpX].getPheromones() / pheromones_sum;
				_ants[ant].setPheromoneVector(tmp, _ants[ant].getX() + tmpX, _ants[ant].getY() + tmpY, weightedPheromones);
				tmp++;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

//Random walk
void GameSystem::randomWalk(int ant)
{
	//If no food detected, random walk
	//Random walk for x-axis
	int tmp = dice(1, 3);
	switch (tmp)
	{
	case 1:
		if (!(_ants[ant].getX() == _gameVector[_ants[ant].getY()].size()))
		{
			_ants[ant].setX(_ants[ant].getX() + 1);
			_ants[ant].setMemory(-1, _ants[ant].getMemoryY());
		}
		break;
	case 2:
		if (!(_ants[ant].getX() == 0))
		{
			_ants[ant].setX(_ants[ant].getX() - 1);
			_ants[ant].setMemory(1, _ants[ant].getMemoryY());
		}
		break;
	case 3:
		_ants[ant].setMemory(0, _ants[ant].getMemoryY());
		break;
	}

	//Random walk for y-axis
	tmp = dice(1, 3);
	switch (tmp)
	{
	case 1:
		if (!(_ants[ant].getY() == _gameVector.size()))
		{
			_ants[ant].setY(_ants[ant].getY() + 1);
			_ants[ant].setMemory(_ants[ant].getMemoryX(), -1);
		}
		break;
	case 2:
		if (!(_ants[ant].getY() == 0))
		{
			_ants[ant].setY(_ants[ant].getY() - 1);
			_ants[ant].setMemory(_ants[ant].getMemoryX(), 1);
		}
		break;
	case 3:
		_ants[ant].setMemory(_ants[ant].getMemoryX(), 0);
		break;
	}

	//Leaves pheromones for other ants TESTING...
	//layPheromones(5.0f, ant);
}

//Pheromone update
void GameSystem::updatePheromones()
{
	for (unsigned int tmpY = 0; tmpY < _gameVector.size(); tmpY++)
	{
		for (unsigned int tmpX = 0; tmpX < _gameVector[tmpY].size(); tmpX++)
		{
			if (_gameVector[tmpY][tmpX].getPheromones() > 0.0)
			{
				_gameVector[tmpY][tmpX].updatePheromones(_evaporation);
			}
		}
	}
}

//Controler position
void GameSystem::setControlerPosition(char input)
{
	if (input == 'a')
	{
		_controler.setXY(_controler.getX() - 3, _controler.getY());
	}
	if (input == 'w')
	{
		_controler.setXY(_controler.getX(), _controler.getY() - 3);
	}
	if (input == 'd')
	{
		_controler.setXY(_controler.getX() + 3, _controler.getY());
	}
	if (input == 's')
	{
		_controler.setXY(_controler.getX(), _controler.getY() + 3);
	}
}




//THIS IS WHERE THE MAIN PART IS DONE!

//Updates the world
void GameSystem::processWorld()
{
	//Updates every ant
	for (unsigned int ant = 0; ant < _ants.size(); ant++)
	{
		int state = _ants[ant].getState();
		switch (state)
		{
			//Has no food and no food detected
		case 0:
			//Update ant movement
			udpateMovement(ant);

			//Detects the food
			foodDetection(ant);
			break;

			//Has food detected
		case 1:
			//Walks to the food nearby
			walkToFood(ant);
			break;

			//Walks with food back
		case 2:
			//Wals to the nest with the food
			walkToNest(ant);
			break;
		}

	}
	//Creates an ant if possible
	createAnt();
	//Updating the pheromones by dissolving over time
	updatePheromones();
}

