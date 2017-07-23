#pragma once

#include "Floor.h"
#include "Ant.h"
#include "Nest.h"
#include "Controler.h"

#include <list>

class GameSystem
{
public:

	//Constructor
	GameSystem(int numAnts, int amountFood, int worldWidth, int worldHeight, int amountFoodNeeded, float evaporation);

	//Destructor
	~GameSystem();

	//Creates an ant
	void createAnt();

	//Prints the world
	void printWorld(sf::RenderWindow &window);

	//Processes the level
	void processWorld();

	//Food detection
	void foodDetection(int a);

	//For laying pheromones for the ant
	void layPheromones(float pheromones, int ant);

	//Walk to the food
	void walkToFood(int a);

	//Walk to the nest
	void walkToNest(int a);

	//Random walk
	void randomWalk(int a);

	//Takes out one target out of the possible pheromone vector
	void findTargetTile(int ant);

	//Updates the movement of the ant
	void udpateMovement(int ant);

	//Detect pheromones
	bool detectPheromones(int a);

	//Hanles the commandprompt
	void setColor(int value);
	void gotoxy(int x, int y);

	//Random engine
	int dice(int min, int max);

	//Update pheromones
	void updatePheromones();

	//Sets the Controler Position
	void setControlerPosition(char input);

private:

	//Vector of ants
	std::vector <Ant> _ants;

	//Nest
	Nest _nest;

	//2-dim Vector of floortiles
	std::vector <std::vector<Floor>> _gameVector;

	//Controler
	Controler _controler;

	//Size of the world
	int _worldHeight = 0;
	int _worldWidth = 0;

	//Stats
	int _amountFoodNeeded = 0;
	float _evaporation = 0.1f;

	//Vector of Textures
	std::list<sf::Texture> _textures;
	sf::Sprite _antSprite;
	sf::Sprite _grassSprite;
	sf::Sprite _appleSprite;
	sf::Sprite _holeSprite;
};