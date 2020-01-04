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