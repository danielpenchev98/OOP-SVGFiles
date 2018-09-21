#include "Console.h"
#include "FigureList.h"
#include <iostream>
#include <fstream>
const std::string initialTags[3] = { "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg Public \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n","<svg>\n","</svg>\n" };
Console::Console()
{
	openedFile = "none";
}
void Console::PrintMenu() const
{
	std::cout << "Available commands :\nopen - use the following command to open a file :open C:\\file.svg\n";
	std::cout << "close - use the following command to close a file :close\nsave - use the following command to save the file :save\n";
	std::cout << "saveas - use the following command to save the information in a new file :saveas C:\\file1.svg\n";
	std::cout << "exit - use the following command to exit the program :exit\n";
	std::cout<< "print - use the following command to print the information :print\n";
	std::cout << "create - use the followings command to create a new figure :\n";
	std::cout << "create <figure> <point>...<point> <stroke color> <stroke width> <fill>\n";
	std::cout << " <line> := create line <x1> <y1> <x2> <y2> <stroke color> <stroke width>\n";
	std::cout << " <circle> := create circle <x> <y> <radius> <stroke color> <stroke width> <fill>\n";
	std::cout << " <rectangle> := create rectangle <x> <y> <height> <width> <stroke color> <stroke width> <fill>";
	std::cout << "<polygon> := create polygon <point1> <point2> ... <point3> <stroke color> <stroke width> <fill>";
	std::cout << "<ellipse> := create ellipse <x> <y> <rx> <ry> <stroke color> <stroke width> <fill>";
	std::cout << "erase - use the following command to erase a figure :erase <id>\n";
	std::cout << "translate - use the following command to translate a figure/all figures :translate vertical=10 horizontal=20/translate <id> vertical=10 horizontal=20\n";
	std::cout << "within - use the following command to print the figures are within a given circle or rectangle :\nwithin <x> <y> <radius>\n";
	std::cout << "within rectangle <x> <y> <height> <width>\n";
}
void Console::UserInput()
{
	std::string input = "";
	std::string extract = "";
	std::ifstream fileGet;
	std::ofstream filePut;
	while (true)
	{
		std::cout << "Please enter a command (type menu for help):";
		std::getline(std::cin, input);
		std::cin.clear();
		std::cout << "Please press enter";
		std::cin.ignore(1000, '\n');
		unsigned int temp = input.find_first_of(" ");
		extract = input.substr(0, temp);
		input = input.substr(temp + 1);
		if (extract == "create"&&openedFile!="none") AddFigure(input);
		else if (extract == "translate"&&openedFile != "none") Translate(input);
		else if (extract == "within"&&openedFile != "none") Within(input);
		else if (extract == "erase"&&openedFile != "none") DeleteFigure(input);
		else if (extract == "open"&&openedFile == "none") Open(input,fileGet);
		else if (extract == "close"&&openedFile != "none") Close(input,fileGet,filePut);
		else if (extract == "save"&&openedFile != "none") Save(filePut);
		else if (extract == "saveas"&&openedFile != "none") SaveAs(input,filePut);
		else if (extract == "menu") PrintMenu();
		else if (extract == "print"&&openedFile != "none") PrintInfo();
		else if (extract == "exit"&&openedFile == "none") break; 
		else std::cout << "Invalid command" << std::endl;
	}
}
int CountSpaces(const std::string& input)
{
	int counter = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') counter++;
	}
	return counter;
}
std::string DeleteSpecificSymbol(const std::string&A, const char toDel)
{
    std::string temp = A;
	for (std::string::iterator iter = temp.begin(); iter != temp.end();)
	{
		if (*iter == toDel)
		{
			temp.erase(iter);
		}
		else ++iter;
	}
	return temp;
}
std::string ReplaceSpecificSymbol(const std::string&A, const char toDel,const char Replace)
{
	std::string temp = A;
	for (int i=0;i<A.size();i++)
	{
		if (temp[i] == toDel)
		{
			temp[i] = Replace;
		}
	}
	return temp;
}
bool CheckIfFound(unsigned int point, std::ifstream& file, std::string& extract)
{
	if (point == std::string::npos) { std::cout << "Invalid command" << std::endl; std::getline(file, extract); return 0; }
	return 1;
}
void Console::Open(const std::string& input,std::ifstream& file) 
{
	//check if it is for instance:open test.svg now
	if (CountSpaces(input) != 0||openedFile!="none")
	{
		std::cout << "Invalid command" << std::endl; return;
	}
	file.open(input, std::ios::in);
	if (!file.good())
	{
		std::cerr << "Coundnt find the file" << std::endl; return;
	}
	openedFile = input;
	std::string toCheck = "";
	std::string extract = "";
	std::getline(file, toCheck);
	std::getline(file, extract);
	toCheck +="\n"+ extract;
	std::getline(file, extract);
	toCheck +="\n" +extract;
	std::getline(file, extract);
	toCheck +="\n" +extract+"\n";
	if (toCheck != initialTags[0] + initialTags[1]) { std::cerr << "Invalid format of file" << std::endl; return; }
	std::getline(file, extract);
	while (extract != "</svg>")
	{

		if (extract[0] != '<' || extract.substr(extract.size() - 3) != " />") { std::cerr << "Invalid format of file" << std::endl; std::getline(file, extract);continue; }
		extract.erase(0,1);
		std::string type = extract.substr(0, extract.find_first_of(" "));
		extract.erase(extract.size() - 3, 3);
		extract = DeleteSpecificSymbol(extract, '\"');
		if (type == "circle")
		{
			unsigned int pointToErase = extract.find("x1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("y1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("radius=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke-width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 13);
			pointToErase = extract.find("fill=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 5);
			AddFigure(extract);
		}
		else if (type == "rectangle")
		{
			unsigned int pointToErase = extract.find("x1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("y1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("height=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 6);
			pointToErase = extract.find("stroke=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke-width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 13);
			pointToErase = extract.find("fill=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 5);
			AddFigure(extract);
		}
		else if (type == "line")
		{
			unsigned int pointToErase = extract.find("x1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("y1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("x2=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("y2=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("stroke=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke-width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 13);
			AddFigure(extract);
		}
		else if (type == "ellipse")
		{
			unsigned int pointToErase = extract.find("x1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("y1=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("rx=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("ry=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 3);
			pointToErase = extract.find("stroke=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke-width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 13);
			pointToErase = extract.find("fill=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 5);
			AddFigure(extract);
		}
		else if (type == "polygon")
		{
			unsigned int pointToErase = 0;
			unsigned int i = 1;
			pointToErase = extract.find("points=");
			if (!CheckIfFound(pointToErase, file, extract)) continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 7);
			pointToErase = extract.find("stroke-width=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 13);
			pointToErase = extract.find("fill=");
			if (!CheckIfFound(pointToErase, file, extract))continue;
			extract.erase(pointToErase, 5);
			extract = ReplaceSpecificSymbol(extract, ',', ' ');
			AddFigure(extract);
		}
		else if (type == "polyline")
		{
		    unsigned int pointToErase = 0;
		    unsigned int i = 1;
		    pointToErase = extract.find("points=");
		    if (!CheckIfFound(pointToErase, file, extract)) continue;
		    extract.erase(pointToErase, 7);
		    pointToErase = extract.find("stroke=");
		    if (!CheckIfFound(pointToErase, file, extract))continue;
		    extract.erase(pointToErase, 7);
		    pointToErase = extract.find("stroke-width=");
		    if (!CheckIfFound(pointToErase, file, extract))continue;
		    extract.erase(pointToErase, 13);
		    extract = ReplaceSpecificSymbol(extract, ',', ' ');
		    AddFigure(extract);
		}
		else
		{
			std::cerr << "Invalid type" << std::endl;
		}
		std::getline(file, extract);
	}
}      
void Console::Close(const std::string&,std::ifstream& fileGet,std::ofstream& filePut) 
{
	fileGet.close();
	filePut.close();
	openedFile = "none";
	list.ContainerClear();
}
void Console::Save(std::ofstream& filePut)
{
	filePut.open(openedFile, std::ofstream::out|std::ofstream::trunc);
	if (!filePut.good())
	{
		std::cout << "Cannot open the file" << std::endl; return;
	}
	filePut << initialTags[0] + initialTags[1];
	std::vector<std::string> temp = list.GetFiguresInSVGFormat();
	for (int i = 0; i<temp.size(); i++)
	{
		filePut << temp[i];
	}
	filePut << initialTags[2];
}
void Console::SaveAs(const std::string& path,std::ofstream& filePut) 
{
	filePut.open(path, std::ofstream::out| std::ofstream::trunc);
	if (!filePut.good())
	{
		std::cout << "Cannot open the file" << std::endl; return;
	}
	filePut << initialTags[0] + initialTags[1];
	std::vector<std::string> temp = list.GetFiguresInSVGFormat();
	for (int i = 0; i < temp.size(); i++)
	{
		filePut << temp[i];
	}
	filePut << initialTags[2];
	filePut.close();
}
void Console::AddFigure(const std::string& input)
{
	unsigned int temp = input.find_first_of(" ");
	list.AddFigure(input.substr(temp+1),input.substr(0,temp));
}
void Console::DeleteFigure(const std::string& input) 
{
	list.DeleteFigure(input);
}
void Console::Translate(const std::string& input) 
{
	list.Translate(input);
}
void Console::Within(const std::string& input) 
{
	list.CheckWithin(input);
}
void Console::PrintInfo() const
{
	list.PrintFigures();
}
