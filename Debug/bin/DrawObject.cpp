#include "rily.h"

void Rily::Rect::Draw(SDL_Renderer *R)
{
	SDL_SetRenderDrawColor(R, this -> r, this -> g, this -> b, this -> a);
	for(int x = 0; x < this -> x + this -> size_x; x++)
	{
		for(int y = 0; y < this -> y + this -> size_y; y++)
		{
			SDL_RenderDrawPoint(R, x, y);
		}
	}
}

void Rily::Tringle::Draw(SDL_Renderer *R)
{
	SDL_SetRenderDrawColor(R, this -> r, this -> g, this -> b, this -> a);
	SDL_RenderDrawLine(R, this -> ax, this -> ay, this -> bx, this -> by);
	SDL_RenderDrawLine(R, this -> ax, this -> ay, this -> cx, this -> cy);
	SDL_RenderDrawLine(R, this -> bx, this -> by, this -> cx, this -> cy);
}

void Rily::DrawingObjects()
{
	for(Rily::Rect 	  R : this -> RectVisibility )
	{
		R.Draw(this->render);
	}

	for(Rily::Tringle T : this -> TringVisibility )
	{		
		T.Draw(this->render);
	}
}