#include <iostream>
#include "Rectangle.h"
#include "Figure.h"
Rectangle::Rectangle(const unsigned int ID):Figure(1,ID),height(0),width(0),fillCol("none")
{
}
Rectangle::Rectangle(const Point&A,const std::string& strCol, const double strWidth, const unsigned int ID, const std::string& fill, const double hei, const double wid):Figure(1,strCol,strWidth,ID),fillCol(fill),height(hei),width(wid)
{
	if (hei <= 0||wid<=0)
	{
		std::cout << "Invalid values for height or width" << std::endl;
		exit(1);
	}
	SetPoint(1, A.x, A.y);
}
Rectangle::Rectangle(const Point&A,const unsigned int ID, const double HEIGHT, const double WIDTH):Figure(1,std::string("none"),1,ID),height(HEIGHT),width(WIDTH)
{
	if (HEIGHT <= 0 || WIDTH <= 0)
	{
		std::cout << "Invalid values for height or width" << std::endl;
		exit(1);
	}
	SetPoint(1, A.x, A.y);
}
Shape Rectangle::GetType() const
{
	return rect;
}
Figure* Rectangle::CopyFigure() const
{
	return new Rectangle(*this);
}

//std::string Rectangle::GetFillColor() const
//{
	//return fillCol;
//}
//void Rectangle::SetFillColor(const std::string&fill)
//{
	//fillCol = fill;
//}
//void Rectangle::SetHeight(const double hei)
//{
	//height = hei;
//}
double Rectangle::GetHeight() const
{
	return  height;
}
//void Rectangle::SetWidth(const double wid)
//{
	//width = wid;
//}
double Rectangle::GetWidth() const
{
	return width;
}
std::string Rectangle::GetInSvgFormat() const
{
	const Point* p1 = GetPoint(1);
	std::string toAdd = "<rectangle x1=\"";
	toAdd += std::to_string(p1->x) + "\" y1=\"" + std::to_string(p1->y) + "\" height=\""+std::to_string(height) + "\" width=\"" + std::to_string(width)+"\" stroke=\"" + GetStrokeColor() + "\" stroke-width=\"" + std::to_string(GetStrokeWidth()) + "\" fill=\"" + fillCol + "\" />\n";
	return toAdd;
}
void Rectangle::Print() const
{
	std::cout << " rectangle ";
	DisplayPoints();
	std::cout << " " << height << " " << width << " " << GetStrokeColor() << " " << GetStrokeWidth() << " " << fillCol << " ID :" << GetId() << std::endl;
}