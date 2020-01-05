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

bool Tringle::PointCheck(int x, int y)
{
	int a = (this->ax - x) * (this->cy - this->ay) - (this->bx - this->ax) * (this->ay - y);
	int b = (this->bx - x) * (this->by - this->by) - (this->cx - this->bx) * (this->by - y);
	int c = (this->cx - x) * (this->ay - this->cy) - (this->ax - this->cx) * (this->cy - y);
	if((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0)) 
	{
		return true;
	} 
	else
	{
		return false;
	}
}


int	Tringle::MaxCoor(int a, int b, int c)
{
	int g;
	a > b ? g = a : g = b;
	g > c ? g = g : g = c; 
	return g;	
}

int	Tringle::MinCoor(int a, int b, int c)
{
	int g;
	a < b ? g = a : g = b;
	g < c ? g = g : g = c; 
	return g;
	return g;	
} 