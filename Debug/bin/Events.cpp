#include "rily.h"

void Rily::Tringle::OnMouse(void (*f)())
{
	this -> On = true;
	this -> OM = f; 
}

void Rily::Tringle::DownClick(void (*f)())
{
	this -> On = true;
	this -> DC = f; 
}

void Rily::Tringle::UpClick(void (*f)())
{
	this -> On = true;
	this -> UC = f; 
}

void Rily::Rect::OnMouse(void (*f)())
{
	this -> On = true;
	this -> OM = f; 
}

void Rily::Rect::DownClick(void (*f)())
{
	this -> On = true;
	this -> DC = f; 
}

void Rily::Rect::UpClick(void (*f)())
{
	this -> On = true;
	this -> UC = f; 
}