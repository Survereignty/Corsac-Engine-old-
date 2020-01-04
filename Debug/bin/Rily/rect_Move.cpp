#include "rily.h"

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

