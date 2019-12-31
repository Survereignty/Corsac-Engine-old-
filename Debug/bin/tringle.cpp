#include "rily.h"

Rily::Tringle::Tringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy)
{
	this -> name = name;
	this -> ax = ax;
	this -> ay = ay;
	this -> bx = bx;
	this -> by = by;
	this -> cx = cx;
	this -> cy = cy;
	this -> center_x = (ax+bx+cx)/2;
	this -> center_y = (ay+by+cy)/2;
}