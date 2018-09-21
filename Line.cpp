#include "Figure.h"
#include "Line.h"
#include <iostream>
Line::Line(const unsigned int ID):Figure(2,ID)
{
}
Line::Line(const Point&A,const Point&B,const std::string& strCol, const double strWidth, const unsigned int ID):Figure(2,strCol,strWidth,ID)
{
	SetPoint(1, A.x, A.y);
	SetPoint(2, B.x, B.y);
}
Shape Line::GetType() const
{
	return line;
}
Figure* Line::CopyFigure() const
{
	return new Line(*this);
}
std::string Line::GetInSvgFormat() const
{
	const Point* p1 = GetPoint(1);
	std::string toAdd = "<line x1=\"";
	toAdd += std::to_string(p1->x) + "\" y1=\"" + std::to_string(p1->y) + "\" x2=\"";
	p1 = GetPoint(2);
	toAdd += std::to_string(p1->x) + " y2=\"" + std::to_string(p1->y) + "\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" />\n";
	return toAdd;
}
void Line::Print() const
{
	std::cout << " line ";
	DisplayPoints();
	std::cout << " " << GetStrokeColor() << " " << GetStrokeWidth() <<" ID :"<<GetId()<< std::endl;
}