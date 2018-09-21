#pragma once
#include <string>
//To determine whether to set the points in Figure.h or in each different figure header
struct Point
{
	double x, y;
	Point():x(0),y(0){}
	Point(double tox,double toy):x(tox),y(toy){}
	Point(const Point&A) :x(A.x), y(A.y){}
};
enum Shape
{
	rect = 0, circle,line ,ellipse,polyline, polygon,Default
};
class Figure
{
	private:
	//Line :2 points,Polygon :Finite points,Rectangle :1 points,Cicle :1 Point,Ellipse :1 Point,Polyline :Finite Points
	Point* points;
	unsigned int numPoints;
	std::string strokeCol;
	double strokeWidth;
	unsigned int id;
	//help functions for the Big 4
	void DeleteFigure();
	void CopyFigure(const Figure&);
protected:
	void DisplayPoints() const;
public:
	Figure(const unsigned int = 0,const unsigned int=0);
	//to add if it is needed constructor Figure(const int , ...) and use va_list,va_args,va_start,va_end()
	Figure(const unsigned int,const std::string&,const double,const unsigned int);
	Figure(const Figure&);
	virtual ~Figure();
	Figure& operator=(const Figure&);
	virtual Shape GetType() const = 0;
	virtual Figure* CopyFigure() const=0;
	void SetStrokeColor(const std::string&);
	std::string GetStrokeColor() const;
	void SetStrokeWidth(const double = 0);
	double GetStrokeWidth() const;
	void SetId(const unsigned int = 0);
	unsigned int GetId() const;
	const Point* const GetPoint(const unsigned int = 0) const;
	unsigned int GetNumberPoints() const;
	void SetPoints(const Point* const);
	void SetPoint(const unsigned int =1,const double=0,const double=0);
	virtual std::string GetInSvgFormat() const=0;
	virtual void Print() const = 0;
	void Translate(const int, const int);
};