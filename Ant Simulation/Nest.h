#pragma once
class Nest
{
public:
	//CONSTRUCTOR
	Nest();
	//DESTRUCTOR
	~Nest();

	//GETTERS
	char getTile();
	int getAmountFood();
	int getHunger();

	//GETTERS COORDINATES
	int getX();
	int getY();

	//SETTERS
	void setTile(char tile);

	//ADDS FOOD TO THE NEST
	void addAmountFood(int amountFood);

	//SETTERS COORDINATES
	void setX(int x);
	void setY(int y);

	//CREATES AN ANT IF ENOUGH FOOD IS IN NEST
	bool creatAntPossible(int amountFoodNeeded);

private:

	//ABILITES OF NEST
	char _tile;
	int _amountFood;

	//COORDINATES OF ANTS
	int _x;
	int _y;
};