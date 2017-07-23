#include "Controler.h"



Controler::Controler()
{
	_x = 0;
	_y = 0;
}


Controler::~Controler()
{
}


//SETTERS
void Controler::setXY(int x, int y)
{
	_x = x;
	_y = y;
}

//GETTERS
int Controler::getX()
{
	return _x;
}
int Controler::getY()
{
	return _y;
}