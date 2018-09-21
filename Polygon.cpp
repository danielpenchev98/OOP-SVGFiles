#include "Figure.h"
#include "Polygon.h"
#include <iostream>
Polygon::Polygon(unsigned int numPoints, unsigned int ID):Figure(numPoints,ID),fillCol("none")
{
}
Polygon::Polygon(const Point* const ptrs, const unsigned int numPtrs, const std::string& strCol, const double strWidth,const unsigned int ID, const std::string& fill):Figure(numPtrs,strCol,strWidth,ID),fillCol(fill)
{
	SetPoints(ptrs);
}
Shape Polygon::GetType() const
{
	return polygon;
}
Figure* Polygon::CopyFigure() const
{
	return new Polygon(*this);
}
void Polygon::Print() const
{
	std::cout << " polygon ";
	DisplayPoints();
	std::cout <<" " << GetStrokeColor() << " " << GetStrokeWidth() << " " << fillCol << " ID :" << GetId() << std::endl;
}
std::string Polygon::GetInSvgFormat() const
{
	std::string toReturn = "<polygon points=\"";
	const Point* temp =nullptr;
	unsigned int num = GetNumberPoints();
	for (int i = 0; i < num; i++)
	{
		temp = GetPoint(i+1);
		toReturn += std::to_string(temp->x) + "," + std::to_string(temp->y);
		if (i != num - 1) toReturn += " ";
	}
	toReturn+= "\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" fill=\"" + fillCol + "\" />\n";
	return toReturn;
}