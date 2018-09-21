#pragma once
#include "Figure.h"
class Line :public Figure
{
public:
	//the argument is ID
	Line(const unsigned int = 0);
	Line(const Point&,const Point&,const std::string&, const double, const unsigned int);
	Shape GetType() const;
	Figure* CopyFigure() const;
    std::string GetInSvgFormat() const;
	void Print() const;
};