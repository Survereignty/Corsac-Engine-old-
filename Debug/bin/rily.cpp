#include "rily.h"

Rily::Rily(SDL_Renderer *r)
{
	this -> render = r;
	std::cout << "Module Rily working!" << std::endl;
}

Rily::Rect* Rily::CreateRect(std::string name, int size_x, int size_y, int x, int y)
{
	Rily::Rect *object = new Rily::Rect(name, size_x, size_y, x, y);
	this -> RectObjects.push_back(*object);
	return object;
}

Rily::Tringle* Rily::CreateTringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy)
{
	Rily::Tringle *object = new Rily::Tringle(name, ax, ay, bx, by, cx, cy);
	this -> TringObjects.push_back(*object);
	return object;
}

void Rily::ChekEvent()
{
//	for(auto object: Rily::TringObjects )
//	{
	//	if(object->On) 
	//}
}