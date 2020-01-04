#include "rily.h"

Tringle::Tringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this -> name 		= name;
	this -> ax 			= ax;
	this -> ay 			= ay;
	this -> bx 			= bx;
	this -> by 			= by;
	this -> cx 			= cx;
	this -> cy 			= cy;
	this -> center_x 	= (ax+bx+cx)/2;
	this -> center_y 	= (ay+by+cy)/2;
	this -> r 			= r;
	this -> g 			= g;
	this -> b 			= b;
	this -> a 			= a;
	this -> const_r 	= r;
	this -> const_g 	= g;
	this -> const_b 	= b;
	this -> const_a 	= a;
}