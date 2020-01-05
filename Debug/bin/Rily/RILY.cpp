#include "rily.h"

void Tringle::Move(int x, int y, int speed)
{
	int speed_x, speed_y;
	if(this -> center_x > x)
	{
		speed_x = -speed;
	}
	else
	{
		speed_x = speed;
	}

	if(this -> center_y > y)
	{
		speed_y = -speed;
	}
	else
	{
		speed_y = speed;
	}

	this -> MoveFinal(x, y, speed_x, speed_y);
}


void Tringle::MoveFinal(int x, int y, int speed_x, int speed_y)
{
	while(this -> center_x != x && this -> center_y != y)
	{
		if(this -> center_x + speed_x > x)
		{
			this -> ax = this -> ax + x;
			this -> bx = this -> bx + x;
			this -> cx = this -> cx + x;
		}
		else if(this -> center_x != x)
		{
			this -> ax += speed_x;
			this -> bx += speed_x;
			this -> cx += speed_x;
		}

		if(this -> center_y + speed_y > y)
		{
			this -> ay = this -> ay + y;
			this -> by = this -> by + y;;
			this -> cy = this -> cy + y;;
		}
		else if(this -> center_y != y)
		{
			this -> ay += speed_y;
			this -> by += speed_y;
			this -> cy += speed_y;
		}
	}
}

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

void Rect::Move(int x, int y, int speed)
{
	int speed_x, speed_y;

	if(this -> x - x >= 0)
	{
		speed_x = -speed;
	}
	else
	{
		speed_x = speed;
	}

	if(this -> y - y >= 0)
	{
		speed_y = -speed;
	}
	else
	{
		speed_y = speed;
	}

	this -> MoveFinal(x, y, speed_x, speed_y);
	std::cout << "YES - 2" << std::endl;
}

void Rect::MoveFinal(int x, int y, int speed_x, int speed_y)
{
	while(this -> x != x && this -> y != y)
	{
		if(this -> x + speed_x > x)
		{
			this -> x = x;
		}
		else
		{
			this -> x += speed_x;
		}

		if(this -> y + speed_y > y)
		{
			this -> y = y;
		}
		else
		{
			this -> y += speed_x;
		}
		std::cout << "YES - 3" << std::endl;
	}
}

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

void Rily::OnMouse(Rect* R, std::function<void(void)> f)
{
	R -> OM = f;
	this -> OnMouseRect.push_back(R);
}

void Rily::UpClick(Rect* R, std::function<void(void)> f)
{
	R -> UC = f; 
	this -> UpClickRect.push_back(R);
}

void Rily::DownClick(Rect* R, std::function<void(void)> f)
{
	R -> DC = f;
	this -> DownClickRect.push_back(R);
}

void Rily::OnMouse(Tringle* T, std::function<void(void)> f)
{
	T -> OM = f;
	this -> OnMouseTringle.push_back(T);
}

void Rily::UpClick(Tringle* T, std::function<void(void)> f)
{
	T -> UC = f; 
	this -> UpClickTringle.push_back(T);
}

void Rily::DownClick(Tringle* T, std::function<void(void)> f)
{
	T -> DC = f;
	this -> DownClickTringle.push_back(T);
}


void Rily::Visibility(Rect *R)
{
	this -> RectVisibility.push_back(R);
}

void Rily::Visibility(Tringle *T)
{
	this -> TringVisibility.push_back(T);
}

void Rect::Draw(SDL_Renderer *R)
{
	SDL_SetRenderDrawColor(R, this->r, this->g, this->b, this->a);
	for(int x = this->x; x <= this -> x + this -> size_x; x++)
	{
		for(int y = this->y; y <= this -> y + this -> size_y; y++)
		{
			SDL_RenderDrawPoint(R, x, y);
		}
	}
}

void Tringle::Draw(SDL_Renderer *R)
{
	SDL_SetRenderDrawColor(R, this -> r, this -> g, this -> b, this -> a);

	SDL_RenderDrawLine(R, this -> ax, this -> ay, this -> bx, this -> by);
	SDL_RenderDrawLine(R, this -> ax, this -> ay, this -> cx, this -> cy);
	SDL_RenderDrawLine(R, this -> bx, this -> by, this -> cx, this -> cy);

	int max_X = this->MaxCoor(this->ax, this->bx, this->cx), 
		max_Y = this->MaxCoor(this->ay, this->by, this->cy), 
		min_X = this->MinCoor(this->ax, this->bx, this->cx), 
		min_Y = this->MaxCoor(this->ay, this->by, this->cy);

	for(int x = min_X; max_X < x; x++)
	{
		for(int y = min_Y; max_Y < y; y++)
		{
			if(this->PointCheck(x, y)) SDL_RenderDrawPoint(R, x, y);
		}
	}
}

void Rily::DrawingObjects()
{
	int x, y;

	SDL_GetMouseState(&x, &y);
	
	AllOnMouse(x, y);

	for(Rect	*R : this -> RectVisibility )
	{
		R->Draw(this->render);
	}

	for(Tringle *T : this -> TringVisibility )
	{
		T->Draw(this->render);
	}

	SDL_RenderPresent(this->render);
}

void FigurePublic::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this -> r = r;
	this -> g = g;
	this -> b = b;
	this -> a = a;
}

void FigurePrivate::DefaultColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this -> const_r = r;
	this -> const_g = g;
	this -> const_b = b;
	this -> const_a = a;
}
