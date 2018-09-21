#pragma once
#include "FigureList.h"
#include <fstream>
//dont want to use Singleton pattern
class Console
{
private:
	FigureList list;
	std::string openedFile;
	void Open(const std::string&,std::ifstream&);
	void Close(const std::string&,std::ifstream&,std::ofstream&);
	void Save(std::ofstream&);
	void SaveAs(const std::string&,std::ofstream&);
	void DeleteFigure(const std::string&);
	void AddFigure(const std::string&);
	void Translate(const std::string&);
	void Within(const std::string&);
	void PrintMenu() const;
	void PrintInfo() const;
public:
	Console();
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;
	void UserInput();
};