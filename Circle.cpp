#include <iostream>
#include "Figure.h"
#include "Circle.h"
Circle::Circle(const unsigned int ID):Figure(1,ID),fillCol("none"),radius(0)
{
}
Circle::Circle(const Point&A,const std::string& strCol, const double strWidth, const unsigned int ID, const std::string& fill,const double rad):Figure(1,strCol,strWidth,ID),fillCol(fill),radius(rad)
{
	if (rad <= 0)
	{
		std::cout << "Invalid value for radius" << std::endl;
		exit(1);
	}
	SetPoint(1, A.x, A.y);
}
Circle::Circle(const Point&A, const unsigned int ID, const double RADIUS):Figure(1,std::string("none"),1,ID),radius(RADIUS)
{
	if (RADIUS <= 0)
	{
		std::cout << "Invalid value for radius" << std::endl;
		exit(1);
	}
	SetPoint(1, A.x, A.y);
}
Shape Circle::GetType() const
{
	return circle;
}
Figure* Circle::CopyFigure() const
{
	return new Circle(*this);
}
/*
std::string Circle::GetFillColor() const
{
	return fillCol;
}
void Circle::SetFillColor(const std::string& fill)
{
	fillCol=fill;
}
void Circle::SetRadius(const double rad)
{
	radius=rad;
}
*/
double Circle::GetRadius() const
{
	return radius;
}
std::string Circle::GetInSvgFormat() const
{
	const Point* p1 = GetPoint(1);
	std::string toAdd = "<circle x1=\"";
	toAdd += std::to_string(p1->x) + "\" y1=\"" + std::to_string(p1->y) + "\" radius=\"" +std::to_string(radius)+ "\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" fill=\""+ fillCol + "\" />\n";
	return toAdd;
}
void Circle::Print() const
{
	std::cout << " circle ";
	DisplayPoints();
	std::cout << " " << radius << " " <<GetStrokeColor()<<" "<<GetStrokeWidth()<<" "<< fillCol <<" ID :"<<GetId()<< std::endl;
}