#pragma once
#include "Figure.h"
class Rectangle :public Figure
{
private:
	std::string fillCol;
	double height;
	double width;
public:
	Rectangle(const unsigned int = 0);
	Rectangle(const Point&,const std::string&, const double, const unsigned int, const std::string&,const double,const double);
	Rectangle(const Point&,const unsigned int, const double, const double);
	Shape GetType() const;
	Figure* CopyFigure() const;
	//std::string GetFillColor() const;
	//void SetFillColor(const std::string&);
	//void SetHeight(const double = 0);
	double GetHeight() const;
	//void SetWidth(const double);
	double GetWidth() const;
	std::string GetInSvgFormat() const;
	void Print() const;
};