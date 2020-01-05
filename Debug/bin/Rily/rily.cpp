#include "rily.h"

Rily::Rily(SDL_Renderer *r)
{
	this -> render = r;
	std::cout << "Module Rily working!" << std::endl;
}

Rily::~Rily()
{
	for(Rect *R : this -> RectObjects )
	{
		delete R;
	}

	for(Tringle *T : this -> TringObjects )
	{
		delete T;
	}
}

Rect* Rily::CreateRect(std::string name, int x, int y, int size_x, int size_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Rect *object = new Rect(name, size_x, size_y, x, y, r, g, b, a);
	this -> RectObjects.push_back(object);
	this -> RectVisibility.push_back(object);
	return object;
}

Tringle* Rily::CreateTringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Tringle *object = new Tringle(name, ax, ay, bx, by, cx, cy, r, g, b, a);
	this -> TringObjects.push_back(object);
	this -> TringVisibility.push_back(object);
	return object;
}

void Rily::ChekEvent(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			AllDClick(e);
			break;
		case SDL_MOUSEBUTTONUP:
			AllUpClick(e);
			break;
	}	
}

void Rily::AllDClick(SDL_Event e)
{
	for(Rect *R : this -> DownClickRect)
	{		
		if(	e.button.x >= R -> x && 
			e.button.y >= R -> y && 
			e.button.x <= R -> x + R -> size_x && 
			e.button.y <= R -> y + R -> size_y )
		{
			R -> OD = true;
			R -> DC();
		}
	}

	for(Tringle *T : this -> DownClickTringle)
	{
		T->PointCheck(e.button.x, e.button.y);	
	}
}

void Rily::AllUpClick(SDL_Event e)
{
	for(Rect *R : this -> UpClickRect)
	{		
			R -> OD = false;
			if(!R -> OB) 
			{
				R -> UC();
			}
			else if(R -> UC)
			{ 
				R -> OM();
			} 
	}

	for(Tringle *T : this -> UpClickTringle)
	{		
		T->PointCheck(e.button.x, e.button.y);
	}
}

void Rily::AllOnMouse(int x, int y)
{
	for(Rect *R : this -> OnMouseRect)
	{		
		if(	x >= R -> x && 
			y >= R -> y && 
			x <= R -> x + R -> size_x && 
			y <= R -> y + R -> size_y &&
			!R -> OD)
		{
			R -> OB = true;
			R -> OM();
		}
		else if(!R -> OD)
		{
			
			R->Color(R -> const_r, R -> const_g, R -> const_b, R -> const_a);
		}

		if(	!(x >= R -> x && 
			y >= R -> y && 
			x <= R -> x + R -> size_x && 
			y <= R -> y + R -> size_y))
		{
			R -> OB = false;
		}
	}

	for(Tringle *T : this -> OnMouseTringle)
	{		
		T->PointCheck(x, y);
	}
}

void Chek()
{
	static int number = 1;
	std::cout << number << std::endl;
	number++;
}