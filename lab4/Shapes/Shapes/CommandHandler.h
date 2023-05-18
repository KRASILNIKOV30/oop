#pragma once
#include <functional>
#include <map>
#include <istream>
#include <vector>
#include "IShape.h"
#include <memory>

class CommandHandler
{
public:
	CommandHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintResult();
	void DrawShapes(SDL_Window* window);

private:
	// const у методов (Исправлено)
	IShape const* GetMaxAreaShape() const;
	IShape const* GetMinPerimeterShape() const;
	void PrintShape(IShape const* shape) const;
	bool AddRectangle(std::istream& args);
	bool AddLine(std::istream& args);
	bool AddCircle(std::istream& args);
	bool AddTriangle(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	//использовать умные указатели (Исправлено)
	std::vector<std::unique_ptr<IShape>> m_shapes;
};

