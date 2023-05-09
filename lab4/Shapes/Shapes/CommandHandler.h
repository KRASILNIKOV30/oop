#pragma once
#include <functional>
#include <map>
#include <istream>
#include <vector>
#include "IShape.h"

class CommandHandler
{
public:
	CommandHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintResult();

private:
	IShape& GetMaxAreaShape();
	IShape& GetMinPerimeterShape();
	void PrintShape(IShape& shape) const;
	bool AddRectangle(std::istream& args);
	bool AddLine(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::vector<IShape*> m_shapes;
};

