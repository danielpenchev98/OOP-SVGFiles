#include "Polyline.h"
#include "Figure.h"
#include <iostream>
Polyline::Polyline(unsigned int numPoints,unsigned int ID):Figure(numPoints,ID)
{

}
Polyline::Polyline(const Point* const ptrs, const unsigned int numPtrs, const std::string& strCol, const double strWidth, const unsigned int ID):Figure(numPtrs,strCol,strWidth,ID)
{
	SetPoints(ptrs);
}
Shape Polyline::GetType() const
{
	return polyline;
}
Figure* Polyline::CopyFigure() const
{
	return new Polyline(*this);
}
void Polyline::Print() const
{
	std::cout << " polyline ";
	DisplayPoints();
	std::cout << " " << GetStrokeColor() << " " << GetStrokeWidth() << " ID :" << GetId() << std::endl;
}
std::string Polyline::GetInSvgFormat() const
{
	std::string toReturn = "<polyline points=\"";
	const Point* temp = nullptr;
	unsigned int num = GetNumberPoints();
	for (int i = 0; i < num; i++)
	{
		temp = GetPoint(i + 1);
		toReturn += std::to_string(temp->x) + "," + std::to_string(temp->y);
		if (i != num - 1) toReturn += " ";
	}
	toReturn += "\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" />\n";
	return toReturn;
}