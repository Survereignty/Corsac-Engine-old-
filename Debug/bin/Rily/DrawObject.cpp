#include "rily.h"

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
}

void Rily::DrawingObjects()
{
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