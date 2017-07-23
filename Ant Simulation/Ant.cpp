#include "Ant.h"


//Constructor
Ant::Ant()
{
	//Sets the properties of the ant
	_x = 0;
	_y = 0;
	_tile = 'A';
	_hunger = 0;
	_foodDetectionRange = 3;
	_state = 0;
	_memoryX = 0;
	_memoryY = 0;

	int tmp = dice(20, 33);
	_foodThatCanBeCarried = tmp;

	for (int i = 0; i < 9; i++)
	{
			PheromoneTarget tmp2;
			_pheromonesVector.push_back(tmp2);
	}
}

//Destructor
Ant::~Ant()
{
}

//Random Engine for integer roll
int Ant::dice(int min, int max)
{
	static std::mt19937 generator((unsigned int)time(NULL));
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

//GETTERS
//Gets the tile as a char
char Ant::getTile() { return _tile; }

//Gets the hunger
int Ant::getHunger() { return _hunger; }

//Gets the food detection range
int Ant::getFoodDetectionRange() { return _foodDetectionRange; }

//Gets the state
int Ant::getState() { return _state; }

//Gets the coordinates
//Gets x
int Ant::getX() { return _x; }
//Gets y
int Ant::getY() { return _y; }

//For locating food
int Ant::getFoodX(){ return _xCoordinateOfFood; }
int Ant::getFoodY() { return _yCoordinateOfFood; }

//For carrying food
int Ant::getFoodCarrying() { return _foodCarrying; }
int Ant::getFoodThatCanBeCarried() { return _foodThatCanBeCarried; }

//Gets the memory of the ant for not walking back where it came from (NOT IMPLEMENTED YET)
int Ant::getMemoryX() { return _memoryX; }
int Ant::getMemoryY() { return _memoryY; }

//Gets if pheromones are detected
bool Ant::getPheromonesDetected() { return _pheromonesDetected; }

//Gets the pheromone vector of this ant
PheromoneTarget Ant::getPheromoneTarget(int id) { return _pheromonesVector[id]; }

//Gets the time until random walk
int Ant::getTimeUntilRandomWalk() { return _timeToRandomWalk; }

//Gets the time until pheromone detection
int Ant::getTimeUntilPheromoneDetection() { return _timeToPheromoneDetection; }

//Setters
//Sets the tile of the ant
void Ant::setTile(char tile) { _tile = tile; }

//Adds hunger with time
void Ant::addHunger(int hunger) { _hunger += hunger; }

//Sets the food detection range
void Ant::setFoodDetectionRange(int foodDetectionRange) { _foodDetectionRange += foodDetectionRange; }

//Sets the state
void Ant::setState(int state) { _state = state; }

//Sets the pheromone vector
void Ant::setPheromoneVector(int id, int x, int y, float pheromones)
{
	_pheromonesVector[id].setX(x);
	_pheromonesVector[id].setY(y);
	_pheromonesVector[id].setPheromones(pheromones);

}

//Sets the coordinates
void Ant::setX(int x) { _x = x; }
void Ant::setY(int y) { _y = y; }

//Sets the memory coordinates
void Ant::setMemory(int memoryX, int memoryY)
{
	_memoryX = memoryX;
	_memoryX = memoryY;
}

//For locating food
void Ant::setFoodX(int x) { _xCoordinateOfFood = x; }
void Ant::setFoodY(int y) { _yCoordinateOfFood = y; }

//Sets if pheromones are detected or not
void Ant::setPheromonesDetected(bool detected) { _pheromonesDetected = detected; }

//Sets the food that is carried
void Ant::setFoodCarrying(int food) { _foodCarrying = food; };

//Sets the food that the ant can carry
void Ant::setFoodThatCanBeCarried(int potentialFoodCarry) { _foodThatCanBeCarried = potentialFoodCarry; }

//Sets the time until random walk
void Ant::setTimeUntilRandomWalk(int time) { _timeToRandomWalk = time; }

//Sets the time until pheromone detection
void Ant::setTimeUntilPheromoneDetection(int time) { _timeToPheromoneDetection  = time; }