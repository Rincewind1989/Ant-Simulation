#pragma once
class Controler
{
public:
	Controler();
	~Controler();

	//SETTERS
	void setXY(int x, int y);

	//GETTERS
	int getX();
	int getY();

private:
	int _x = 0;
	int _y = 0;
};

