#include <iostream>
#include "Figure.h"
#include <exception>
Figure::Figure(const unsigned int num,const unsigned int ID):points(nullptr),numPoints(0),strokeCol("none"),strokeWidth(0),id(ID)
{
	if (num != 0)
	{
		points = new Point[num];
		numPoints = num;
	}
	else
	{
		points = nullptr;
	}
}
//to add if it is needed constructor Figure(const int , ...) and use va_list,va_args,va_start,va_end()
//If the user uses this constructor, the number of Points should be valid , otherwise he shouldnt have used it
Figure::Figure(const unsigned int num, const std::string&strCol, const double strWidth,const unsigned int ID):numPoints(num),strokeCol(strCol),strokeWidth(strWidth),id(ID)
{
	
	try
	{
		if (numPoints == 0||strWidth<=0)
		{
			throw std::invalid_argument("Cannot use this constructor if the number of Points is 0 or less");
		}
		points = new Point[numPoints];
	}
	catch(const std::invalid_argument& err)
	{
		std::cout << err.what() << std::endl;
		exit(1);
	}
	catch (const std::bad_alloc& all)
	{
		std::cout << all.what() << std::endl;
		exit(1);
	}
}
Figure::Figure(const Figure&A)
{
	CopyFigure(A);
}
Figure::~Figure()
{
	DeleteFigure();
}
Figure& Figure::operator=(const Figure&A)
{
	if (this != &A)
	{
		DeleteFigure();
		CopyFigure(A);
	}
	return *this;
}
void Figure::DeleteFigure()
{
	delete[] points;
}
//not exception safe.Should use it copy-swap strategy
void Figure::CopyFigure(const Figure&A)
{
	this->numPoints = A.numPoints;
	points = new Point[numPoints];
	this->strokeCol = A.strokeCol;
	this->strokeWidth = A.strokeWidth;
	this->id = A.id;
	for (int i = 0; i < numPoints; i++)
	{
		points[i].x = A.points[i].x;
		points[i].y = A.points[i].y;
	}
}
Shape Figure::GetType() const
{
	return Default;
}
void Figure::SetStrokeColor(const std::string& toSet)
{
	strokeCol = toSet;
}
std::string Figure::GetStrokeColor() const
{
	return strokeCol;
}
void Figure::SetStrokeWidth(const double wid)
{
	if (wid < 0)
	{
		std::cout << "Error invalid Stroke width" << std::endl;
		return;
	}
	strokeWidth = wid;
}
double Figure::GetStrokeWidth() const
{
	return strokeWidth;
}
void Figure::SetId(const unsigned int ID)
{
	this->id = ID;
}
unsigned int Figure::GetId() const
{
	return id;
}
void Figure::SetPoints(const Point* const ptrs)
{
	if (points == nullptr)
	{
		std::cout << "Cannot be done" << std::endl;
		return;
	}
	for (int i = 0; i < numPoints; i++)
	{
		points[i].x = ptrs[i].x;
		points[i].y = ptrs[i].y;
	}
}
void Figure::SetPoint(const unsigned int pos,const double x,const double y)
{
	if (pos > numPoints)
	{
		std::cout << "Invalid Position" << std::endl;
		return;
	}
	points[pos-1].x = x;
	points[pos-1].y = y;
}
const Point* const Figure::GetPoint(const unsigned int pos) const
{
	if (pos > numPoints)
	{
		std::cerr << "Out of range" << std::endl;
		return nullptr;
	}
	return &points[pos - 1];
}
void Figure::DisplayPoints() const
{
	for (int i = 0; i < numPoints; i++)
	{
		std::cout << " "<< points[i].x << " " << points[i].y;
	}
}
void Figure::Print() const
{
	std::cout <<" ID :"<<GetId()<< " stroke color :" << GetStrokeColor() << " stroke width :" << GetStrokeWidth();
	DisplayPoints();
}
void Figure::Translate(const int vertical, const int  horizontal)
{
	for (int i = 0; i < numPoints; i++)
	{
		points[i].x += horizontal;
		points[i].y += vertical;
	}
}
unsigned int Figure::GetNumberPoints() const
{
	return numPoints;
}