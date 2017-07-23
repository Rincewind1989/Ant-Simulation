#pragma once

#include <vector>
#include <random>
#include <time.h>

//Pheromone detection class for ant
//(THIS CLASS IS PUT INTO A VECTOR FOR THE ANT TO SAVE THE PHEROMONE LEVEL AROUND IT AND THE X AND Y COORDINATES OF THE TARGET FIELD)
class PheromoneTarget
{
public:
	PheromoneTarget() {}
	~PheromoneTarget() {}

	//Getters and setters
	int getX() { return _x; };
	int getY() { return _y; };
	float getPheromones() { return _pheromones; };

	void setX(int x) { _x = x; };
	void setY(int y) { _y = y; };
	void setPheromones(float pheromones) { _pheromones = pheromones; };
private:
	int _x = 0;
	int _y = 0;
	float _pheromones = 0.0f;
};

//ANT CLASS HEADER
class Ant
{
public:
	Ant();
	~Ant();

	//Random engine
	int dice(int min, int max);

	//Getters
	char getTile();
	int getHunger();
	int getFoodDetectionRange();
	int getState();

	//Getters coordinates
	int getX();
	int getY();

	//For located food
	int getFoodX();
	int getFoodY();

	//For carrying food
	int getFoodCarrying();
	int getFoodThatCanBeCarried();

	//Gets the memory of the ant for not walking back where it came from (NOT IMPLEMENTED YET)
	int getMemoryX();
	int getMemoryY();

	//Gets if pheromones are detected
	bool getPheromonesDetected();

	//For the pheromone target vector
	PheromoneTarget getPheromoneTarget(int id);

	//Get the randomWalk time state
	int getTimeUntilRandomWalk();

	//Gets the time until pheromone detection
	int getTimeUntilPheromoneDetection();

	//Setters
	void setTile(char tile);

	//Adds hunger over time
	void addHunger(int hunger);

	//Sets the food detection range
	void setFoodDetectionRange(int foodDetectionRange);

	//Sets the State
	void setState(int state);

	//Sets the pheromone vector of the ant
	void setPheromoneVector(int id, int x, int y, float pheromones);

	//Gets the memory of the ant for not walking back where it came from (NOT IMPLEMENTED YET)
	void setMemory(int memoryX, int memoryY);

	//Setters coordinates
	void setX(int x);
	void setY(int y);

	//For located food
	void setFoodX(int x);
	void setFoodY(int y);

	//For carrying food
	void setFoodCarrying(int food);
	void setFoodThatCanBeCarried(int potentialFoodCarry);

	//Sets if pheromones are detected
	void setPheromonesDetected(bool detected);

	//Sets the time until random walk
	void setTimeUntilRandomWalk(int time);

	//Sets the time until pheromone detection
	void setTimeUntilPheromoneDetection(int time);

private:

	//Condition of ant
	char _tile;
	int _hunger = 0;
	int _state;
	int _timeToRandomWalk = 0;
	int _timeToPheromoneDetection = 0;

	//Food detection/carry abilities
	int _foodDetectionRange;
	int _xCoordinateOfFood;
	int _yCoordinateOfFood;
	int _memoryX;
	int _memoryY;
	bool _pheromonesDetected;
	int _pheromonesDetectionRange;
	int _foodCarrying;
	int _foodThatCanBeCarried;

	//Coordinates of ant
	int _x;
	int _y;

	//Pheromones vector for aroung the ant
	std::vector <PheromoneTarget> _pheromonesVector;
};
