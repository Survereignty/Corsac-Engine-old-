	#include "rily.h"

Rily::Rect::Rect(std::string name, int size_x, int size_y, int x, int y)
{
	this -> name   = name;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> x      = x;
	this -> y      = y;
}