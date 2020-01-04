#include "rily.h"

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
