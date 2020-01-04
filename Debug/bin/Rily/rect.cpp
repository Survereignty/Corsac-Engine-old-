#include "rily.h"

Rect::Rect(std::string name, int size_x, int size_y, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this -> name 	= name;
	this -> size_x	= size_x;
	this -> size_y	= size_y;
	this -> x 		= x;
	this -> y 		= y;
	this -> r 		= r;
	this -> g 		= g;
	this -> b 		= b;
	this -> a 		= a;
	this -> const_r = r;
	this -> const_g = g;
	this -> const_b = b;
	this -> const_a = a;
}