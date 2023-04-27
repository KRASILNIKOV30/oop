#include "Calculator.h"
#include <functional>
#include <map>

class CommandHandler
{
public:
	CommandHandler(Calculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	bool PrintVars(std::istream& args);
	bool PrintFns(std::istream& args);
	bool DefineVar(std::istream& args);
	bool DefineFn(std::istream& args);
	bool LetVar(std::istream& args);
	bool Print(std::istream& args);
	bool ParseLetExpression(std::string exp, std::string& leftOperand, std::string& rightOperand);
	bool ParseFnExpression(std::string exp, std::string& name, std::string& leftOperand, std::string& operation, std::string& rightOperand);
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};