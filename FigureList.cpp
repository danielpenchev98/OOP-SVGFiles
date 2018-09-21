#include "Circle.h"
#include "Figure.h"
#include "FigureList.h"
#include "Rectangle.h"
#include "Line.h"
#include <iostream>
#include <algorithm>
#include "Ellipse.h"
#include "Polygon.h"
#include "Polyline.h"
FigureList::FigureList(const FigureList&A)
{
	CopyList(A);
}
FigureList::~FigureList()
{
	DeleteList();
}
FigureList& FigureList::operator=(const FigureList&A)
{
	if (this != &A)
	{
		DeleteList();
		CopyList(A);
	}
	return *this;
}
void FigureList::DeleteList()
{
	std::vector<Figure*>::iterator iter;
	for (iter = list.begin(); iter !=list.end(); ++iter)
	{
		delete *iter;
	}
	list.clear();
}
void FigureList::CopyList(const FigureList&A)
{
	for (int i = 0; i < A.list.size(); i++)
	{
		this->list.push_back(A.list[i]->CopyFigure());
	}
}
bool ValidIntDoubleFloat(const std::string& isVal)
{
	int counterDots = 0;
	for (int i = 0; i < isVal.size(); i++)
	{
		if (isVal[0] == '-')continue; 
		if (isVal[i] == '.'&&counterDots <= 1) counterDots++;
		else if (isVal[i]<'0' || isVal[i]>'9') return 0;
	}
	return 1;
}
std::size_t SpecialCountSymbol(std::string&A, char c)
{
	std::size_t counter = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == ' ')
		{
			counter++;
			if (i+1 != A.size()&&A[i+1]==' ')
			{
				counter++;
			}
		}
	}
	return counter;
}
bool Exctract(double& toAdd,std::string& rest)
{
	unsigned int fsymb = rest.find_first_of(" ");
	std::string tempString = rest.substr(0, fsymb);
    if (!ValidIntDoubleFloat(tempString))
	{
   	    std::cout << "Error invalid input" << std::endl;
        return 1;
    }
    toAdd = std::stod(tempString);
	rest = rest.substr(fsymb + 1);
	return 0;
}
void Exctract(std::string& toAdd, std::string& rest)
{
	unsigned int fsymb = rest.find_first_of(" ");
	toAdd = rest.substr(0, fsymb);
	rest = rest.substr(fsymb + 1);
}
void FigureList::AddFigure(const std::string& input,const std::string& typeFig)
{
	//create <figure> <points> <additionalPoints> <color>
	//<rectangle> := create rectangle <x> <y> <width> <height> <stroke color> <stroke width> <color>
	//<circle> := create circle <x> <y> <r> <stroke color> <stroke width> <color>
	//<line> := create line <x1> <y1> <x2> <y2> <stroke color> <stroke width>
	//<polygon> := create polygon <point1> <point2> ... <pointN> <color>
	//create rectangle 1000 1000 10 20 yellow
	std::string rest = input;
	unsigned int id=0;
	bool flag = 0;
	while (true)
	{
		flag = 0;
		std::cout << "Enter ID for the new Figure :";
		std::cin >> id;
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->GetId() == id)
			{
				std::cerr << "Error.A figure with that id has been found" << std::endl;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
		else
		{
			std::cin.clear();
			std::cout << "Please press enter"<<std::endl;
			std::cin.ignore();
		}
	}
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::size_t spaceCounter = SpecialCountSymbol(rest, ' ');
	if (typeFig == "rectangle")
	{
		if (spaceCounter != 6)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;
		
		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;
		
		//getting height
		double height = 0;
		if (Exctract(height, rest)) return;

		//getting width
		double width = 0;
		if (Exctract(width, rest)) return;

		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);
		
		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;

		//getting fill color
		std::string fillCol = rest;
		Figure* toPush = new Rectangle(Point(x1,y1), strCol, strWidth, id, fillCol, height, width);
		list.push_back(toPush);
		std::cout << "The figure has been added" << std::endl;
	}
	else if (typeFig == "circle")
	{
		if (spaceCounter != 5)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;

		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;

		//getting radius
		double radius = 0;
		if (Exctract(radius, rest)) return;
		
		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);

		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;

		//getting fill color
		std::string fillCol = rest;
		Figure* toPush = new Circle(Point(x1, y1), strCol, strWidth, id, fillCol,radius);
		list.push_back(toPush);
		std::cout << "The figure has been added" << std::endl;
	}
	else if (typeFig == "line")
	{
		if (spaceCounter != 5)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;

		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;

		//getting x2
		double x2 = 0;
		if (Exctract(x2, rest)) return;

		//getting y2
		double y2 = 0;
		if (Exctract(y2, rest)) return;

		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);

		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;
		Figure* toPush = new Line(Point(x1, y1), Point(x2, y2), strCol, strWidth, id);
		list.push_back(toPush);
		std::cout << "The figure has been added" << std::endl;
	}
	else if (typeFig == "ellipse")
	{
		if (spaceCounter != 6)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;

		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;

		//getting rx
		double rx = 0;
		if (Exctract(rx, rest)) return;

		//getting ry
		double ry = 0;
		if (Exctract(ry, rest)) return;

		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);

		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;

		//getting fill color
		std::string fillCol = rest;
		Figure* toPush = new Ellipse(Point(x1, y1), strCol, strWidth, id, fillCol,rx , ry);
		list.push_back(toPush);
		std::cout << "The figure has been added" << std::endl;
	}
	else if (typeFig == "polyline")
	{
		if (spaceCounter < 7)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting Points
		int counter = spaceCounter - 1;
		Point* ptr = new Point[counter];
		unsigned int i = 0;
		while (counter)
		{
			//getting x
			double x1 = 0;
			if (Exctract(x1, rest))  return;

			//getting y
			double y1 = 0;
			if (Exctract(y1, rest)) return;

			ptr[i].x = x1;
			ptr[i].y = y1;
			i++;
			counter -= 2;
		}
		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);

		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;

		Figure* toPush = new Polyline(ptr,i, strCol, strWidth, id);
		list.push_back(toPush);
		delete[] ptr;
		std::cout << "The figure has been added" << std::endl;
	}
	else if (typeFig == "polygon")
	{
		if (spaceCounter < 8)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting Points
		int counter = spaceCounter - 2;
		Point* ptr = new Point[counter];
		unsigned int i = 0;
		while (counter)
		{
			//getting x
			double x1 = 0;
			if (Exctract(x1, rest))  return;

			//getting y
			double y1 = 0;
			if (Exctract(y1, rest)) return;

			ptr[i].x = x1;
			ptr[i].y = y1;
			i++;
			counter-=2;
		}
		//getting stroke color
		std::string strCol = "";
		Exctract(strCol, rest);

		//getting stroke width
		double strWidth = 0;
		if (Exctract(strWidth, rest)) return;

		//getting fill color
		std::string fillCol = rest;
		Figure* toPush = new Polygon(ptr,i,strCol,strWidth,id,fillCol);
		list.push_back(toPush);
		delete[] ptr;
		std::cout << "The figure has been added" << std::endl;
	}
	else
	{
		std::cout << "Invalid type" << std::endl;
	}
	
}
void FigureList::DeleteFigure(const std::string& input)
{
	//from the command :" erase 1 "for example, the InputMaster will remove "erase " and it will us "1" as argument for this function
	if (ValidIntDoubleFloat(input))
	{
		int id = std::stoi(input);
		if (id < 0||id!=std::stod(input))
		{
			std::cout << "Invalid id" << std::endl;
			return;
		}
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->GetId() == id)
			{
				std::cout << "The figure with the id " << id << " has been erased" << std::endl;
				delete list[i];
				list.erase(list.begin() + i);
				return;
			}
		}
	}
	std::cout <<"There is no figure with that id "<< std::endl;
}
void FigureList::PrintFigures() const
{
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << i << ".";
		list[i]->Print();
	}
}
void FigureList::Translate(const std::string& input)
{
	std::string temp = input;
	int id = 0;
	std::string extract = "";
	unsigned int spacecount = SpecialCountSymbol(temp, ' ');
	unsigned int first = 0;
	if (spacecount == 1)
	{
		id == -1;
	}
	else if (spacecount == 2)
	{//getting only the id
		first = temp.find_first_of(" ");
		extract = temp.substr(0, first);
		if(!ValidIntDoubleFloat(extract)) std::cerr << "Error.Invalid command" << std::endl;return;
		id = std::stoi(extract);
		temp = temp.substr(first + 1);
	}
	else
	{
		std::cerr << "Error.Invalid command" << std::endl;
		return;
	}

	//getting the vertical value
	first = temp.find_first_of(" ");
	extract = temp.substr(10, first - 1);
	if (temp.substr(0, 10) != "vertical=\"" || temp[first - 1] != '\"'|| !ValidIntDoubleFloat(extract)) std::cerr << "Error.Invalid command" << std::endl; return;
	double vertical = std::stod(extract);
	
	//getting the horizontal value
	temp = temp.substr(first + 1);
	first = temp.find_first_of(" ");
	extract = temp.substr(12, first - 1);
	if(temp.substr(0,12)!="horizontal=\""||temp[first-1]!='\"'||!ValidIntDoubleFloat(extract))  std::cerr << "Error.Invalid command" << std::endl; return;
	double horizontal = std::stod(extract);
	
	for (int i = 0; i < list.size(); i++)
	{
		if (id == -1||(list[i]->GetId() == id && id != -1 ))
		{
			list[i]->Translate(vertical, horizontal);
		}
	}
	std::cout << "The figure/s has/ve been translated" << std::endl;
}
bool FigureList::IsWithin(const Figure* const curr, const Circle* const toCompare) const
{
	Shape type = curr->GetType();
	//when the type is rect whe use the same technique as when you have to deal with circle
	if (type == rect)
	{
		const Point* rpt1 = curr->GetPoint(1);
		const Point* cpt1 = toCompare->GetPoint(1);
		const double height = ((Rectangle*)curr)->GetHeight();
		const double width = ((Rectangle*)curr)->GetWidth();
		const double radius = toCompare->GetRadius();
		if (sqrt((rpt1->x - cpt1->x)*(rpt1->x - cpt1->x) + (rpt1->y - cpt1->y)*(rpt1->y - cpt1->y)) > radius) return false;
		else if (sqrt((rpt1->x + width - cpt1->x)*(rpt1->x +width - cpt1->x) + (rpt1->y - cpt1->y)*(rpt1->y - cpt1->y)) >radius) return false;
		else if (sqrt((rpt1->x - cpt1->x)*(rpt1->x - cpt1->x) + (rpt1->y - height - cpt1->y)*(rpt1->y - height - cpt1->y)) > radius) return false;
		else if(sqrt((rpt1->x+width - cpt1->x)*(rpt1->x+width - cpt1->x) + (rpt1->y - height - cpt1->y)*(rpt1->y - height - cpt1->y)) > radius) return false;
		return true;
	}
	else if (type == circle)
	{
		const Point* cpt1 = curr->GetPoint(1);
		const Point* cptr2 = toCompare->GetPoint(1);
		if (sqrt((cpt1->x - cptr2->x)*(cpt1->x - cptr2->x) + (cpt1->y - cptr2->y)*(cpt1->y - cptr2->y)) + ((Circle*)curr)->GetRadius() > toCompare->GetRadius()) return false;
		return true;
	}
	else if (type == line)
	{
		const Point* lpt1 = curr->GetPoint(1);
		const Point* lpt2 = curr->GetPoint(2);
		const Point* cpt1 = toCompare->GetPoint(1);
		if (sqrt((lpt1->x - cpt1->x)*(lpt1->x - cpt1->x) + (lpt1->y - cpt1->y)*(lpt1->y - cpt1->y)) > toCompare->GetRadius()) return false;
		else if (sqrt((lpt2->x - cpt1->x)*(lpt2->x - cpt1->x) + (lpt2->y - cpt1->y)*(lpt2->y - cpt1->y)) > toCompare->GetRadius()) return false;
		return true;
	}
	else if (type == polygon||type==polyline)
	{
		int numPoints = curr->GetNumberPoints();
		const Point* temp = nullptr;
		const Point* ctemp = toCompare->GetPoint(1);
		for (int i = 0; i < numPoints; i++)
		{
			temp = curr->GetPoint(i);
			if (sqrt((temp->x - ctemp->x)*(temp->x - ctemp->x) + (temp->y - ctemp->y)*(temp->y - ctemp->y)) > toCompare->GetRadius()) return 0;
		}
		return 1;
	}
	else if (type == ellipse)
	{
		const Point* etemp = curr->GetPoint(1);
		const Point* ctemp = toCompare->GetPoint(1);
		double radius = toCompare->GetRadius();
		double rx = ((Ellipse*)curr)->GetRX();
		double ry = ((Ellipse*)curr)->GetRY();
		if (etemp->x + rx > ctemp->x + radius || etemp->x - rx<ctemp->x - radius || etemp->y + ry>ctemp->y + radius || etemp->y - ry < ctemp->y - radius) return 0;
		return 1;
	}
	else
	{
		std::cout << "Unsupported type" << std::endl;
		return false;
	}
}
bool FigureList::IsWithin(const Figure* const curr, const Rectangle* const toCompare) const
{
	Shape type = curr->GetType();
	const Point* rpt1 = toCompare->GetPoint(1);
	const double height1 = toCompare->GetHeight();
	const double width1 = toCompare->GetWidth();
	if (type == rect)
	{
		const double height2 = ((Rectangle*)curr)->GetHeight();
		const double width2 = ((Rectangle*)curr)->GetWidth();
		const Point* rpt2 = curr->GetPoint(1);
		if (rpt2->x < rpt1->x || rpt2->y > rpt1->y)return false;
		else if (rpt2->x + width2 > rpt1->x + width1) return false;
		else if (rpt2->y - height2 < rpt1->y - height1)return false;
		return true;
	}
	else if (type == circle)
	{
		const Point* cpt1 = curr->GetPoint(1);
		const double radius = ((Circle*)curr)->GetRadius();
		if (rpt1->y<cpt1->y + radius || rpt1->y - height1>cpt1->y - radius || rpt1->x > cpt1->x - radius || rpt1->x + width1 < cpt1->x + radius)return false;
		return true;
	}
	else if (type == line)
	{
		const Point* lpt1 = curr->GetPoint(1);
		const Point* lpt2 = curr->GetPoint(2);
		//if the both points are inside the ractangle
		if ((lpt1->y > rpt1->y - height1 && lpt1->y < rpt1->y&&lpt1->x>rpt1->x&&lpt1->x<rpt1->x+width1)&& (lpt2->y > rpt1->y - height1 && lpt2->y < rpt1->y&&lpt2->x>rpt1->x&&lpt2->x < rpt1->x + width1))return true;
		return false;
	}
	else if (type == polygon||type==polyline)
	{
		//maybe fail?
		const Point* ptemp = nullptr;
		for (int i = 0; i < curr->GetNumberPoints(); i++)
		{
			if (ptemp->x<rpt1->x || ptemp->x>rpt1->x + width1 || ptemp->y<rpt1->y - height1 || ptemp->y>rpt1->y) return 0;
		}
		return 1;
	}
	else if (type == ellipse)
	{
		const Point* etemp = curr->GetPoint(1);
		double rx = ((Ellipse*)curr)->GetRX();
		double ry = ((Ellipse*)curr)->GetRY();
		if (etemp->x - rx<rpt1->x || etemp->x + rx>rpt1->x + width1 || etemp->y + ry > rpt1->y || etemp->y - ry < rpt1->y - height1) return 0;
		return 1;
	}
	else
	{
		std::cout << "Unsupported type" << std::endl;
	}
	return 0;
}
void FigureList::CheckWithin(const std::string& input) const
{
	std::string rest = input;
	std::size_t fsymb = rest.find_first_of(" ");
	std::string type = rest.substr(0, fsymb);
	rest = rest.substr(fsymb + 1);
	std::size_t spaceCounter = SpecialCountSymbol(rest, ' ');
	if (type == "rectangle")
	{
		if (spaceCounter != 3)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;

		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;

		//getting height
		double height = 0;
		if (Exctract(height, rest)) return;

		//getting width
		double width = 0;
		if (Exctract(width, rest)) return;

		Rectangle toCompare(Point(x1,y1),1,height,width);
		std::cout << "The figures within this rectangle are :" << std::endl;
		for (int i = 0; i < list.size(); i++)
		{
			if (IsWithin(list[i], &toCompare)) list[i]->Print();
		}
	}
	else if (type == "circle")
	{
		if (spaceCounter != 2)
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		//getting x1
		double x1 = 0;
		if (Exctract(x1, rest)) return;

		//getting y1
		double y1 = 0;
		if (Exctract(y1, rest)) return;

		//getting radius
		double radius = 0;
		if (Exctract(radius, rest)) return;

		Circle toCompare(Point(x1, y1), 1, radius);
		std::cout << "The figures within this circle are :" << std::endl;
		for (int i = 0; i < list.size(); i++)
		{
			if (IsWithin(list[i], &toCompare)) list[i]->Print();
		}
	}
}
std::vector<std::string> FigureList::GetFiguresInSVGFormat() const
{
	std::vector<std::string> container;
	for (int i = 0; i<list.size(); i++)
	{
		container.push_back(list[i]->GetInSvgFormat());
	}
	return container;
}
void FigureList::ContainerClear()
{
	DeleteList();
}