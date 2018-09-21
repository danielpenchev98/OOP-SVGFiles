#pragma once
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include <vector>
class FigureList
{
private:
	std::vector<Figure*> list;
	void DeleteList();
	void CopyList(const FigureList&);
public:	
	bool IsWithin(const Figure* const, const Rectangle* const) const;
	bool IsWithin(const Figure* const, const Circle* const) const;
public:
	FigureList() {}
	FigureList(const FigureList&);
	~FigureList();
	FigureList& operator=(const FigureList&);
	//to determine ID inside function void AddFigure();
	//DOESNT WORT WITH LINE , ONLY the first point can be modiefied run-time
	void AddFigure(const std::string&,const std::string&);
	void DeleteFigure(const std::string&);
	void PrintFigures() const;
	void Translate(const std::string&);
	void CheckWithin(const std::string&) const;
	void ContainerClear();
	std::vector<std::string> GetFiguresInSVGFormat() const;
};