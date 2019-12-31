#include "rily.h"

void Rily::Visibility(Rily::Rect *R)
{
	this -> RectVisibility.push_back(*R);
}

void Rily::Visibility(Rily::Tringle *T)
{
	this -> TringVisibility.push_back(*T);
}