#pragma once
#include "Figure.h"
class Ellipse:public Figure
{
private:
	std::string fillCol;
	double radx;
	double rady;
public:
	Ellipse(const unsigned int = 0);
	Ellipse(const Point&, const std::string&, const double, const unsigned int, const std::string&, const double, const double);
	Shape GetType() const;
	Figure* CopyFigure() const;
	void Print() const;
	std::string GetInSvgFormat() const;
	double GetRX() const { return radx; }
	double GetRY() const { return rady; }
};