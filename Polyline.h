#pragma once
#include "Figure.h"
class Polyline :public Figure
{
public:
	Polyline(unsigned int = 3, unsigned int = 0);
	Polyline(const Point* const, const unsigned int, const std::string&, const double, const unsigned int);
	Shape GetType() const;
	Figure* CopyFigure() const;
	void Print() const;
	std::string GetInSvgFormat() const;
};