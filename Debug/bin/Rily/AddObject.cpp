#include "rily.h"

void Rily::Visibility(Rect *R)
{
	this -> RectVisibility.push_back(R);
}

void Rily::Visibility(Tringle *T)
{
	this -> TringVisibility.push_back(T);
}