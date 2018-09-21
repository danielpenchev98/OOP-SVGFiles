#pragma once
#include "Figure.h"
class Polygon :public Figure
{
private:
	std::string fillCol;
public:
	Polygon(unsigned int = 3,unsigned int =0);
	Polygon(const Point* const, const unsigned int, const std::string&, const double, const unsigned int, const std::string&);
	Shape GetType() const;
	Figure* CopyFigure() const;
	void Print() const;
	std::string GetInSvgFormat() const;
};