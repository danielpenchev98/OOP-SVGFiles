#pragma once
#include "Figure.h"
class Circle:public Figure
{
private:
	std::string fillCol;
	double radius;
public:
	Circle(const unsigned int = 0);
	Circle(const Point&,const std::string&, const double, const unsigned int, const std::string&,const double);
	Circle(const Point&, const unsigned int, const double);
	Shape GetType() const;
	Figure* CopyFigure() const;
	//std::string GetFillColor() const;
	//void SetFillColor(const std::string&);
	//void SetRadius(const double = 0);
	double GetRadius() const;
	std::string GetInSvgFormat() const;
	void Print() const;
};