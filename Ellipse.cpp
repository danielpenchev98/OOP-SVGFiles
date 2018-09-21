#include "Ellipse.h"
#include "Figure.h"
#include <iostream>
Ellipse::Ellipse(const unsigned int ID):Figure(1,ID),fillCol("none"),radx(0),rady(0)
{

}
Ellipse::Ellipse(const Point& ptr, const std::string& strCol, const double strWidth, const unsigned int ID, const std::string& fill, const double rx, const double ry):Figure(1,strCol,strWidth,ID),radx(rx),rady(ry),fillCol(fill)
{
	if (rx <= 0 || ry <= 0)
	{
		std::cout << "Invalid values" << std::endl;
		exit(1);
	}
	SetPoint(1, ptr.x, ptr.y);
}
Shape Ellipse::GetType() const
{
	return ellipse;
}
Figure* Ellipse::CopyFigure() const
{
	return new Ellipse(*this);
}
void Ellipse::Print() const
{
	std::cout << " ellipse ";
	DisplayPoints();
	std::cout << " " << radx << " " << rady << " " << GetStrokeColor() << " " << GetStrokeWidth() << " " << fillCol << " ID :" << GetId() << std::endl;
}
std::string Ellipse::GetInSvgFormat() const
{
	const Point* p1 = GetPoint(1);
	std::string toAdd = "<ellipse x1=\"";
	toAdd += std::to_string(p1->x) + "\" y1=\"" + std::to_string(p1->y) + "\" rx=\"" + std::to_string(radx) + "\" ry=\"" + std::to_string(rady) + "\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" fill=\"" + fillCol + "\" />\n";
	return toAdd;
}