#pragma once
class Floor
{
public:
	Floor();
	~Floor();

	//Random Engine
	int dice(int min, int max);

	//GETTERS
	char getTile();
	bool getFood();
	int getAmountFood();
	float getPheromones();

	//SETTERS
	void setTile(char tile);
	void setFood(bool hasFood);

	void updatePheromones(float evaporation);

	//ADDS OR SUBTRACTS FOOD
	void addFood(int addFood);

	//ADDS OR SUBTRACTS PHEROMONES
	void addPheromones(float addpheromones);

private:
	char _tile = '.';
	bool _hasFood = false;
	int _amountFood = 0;

	//TRACKWEIGHT FOR ANTS
	float _pheromones = 0.0f;

};
