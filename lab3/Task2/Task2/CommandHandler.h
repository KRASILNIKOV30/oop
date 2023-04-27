#include "Calculator.h"
#include <functional>
#include <map>

class CommandHandler
{
public:
	CommandHandler(Calculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	bool PrintVars(std::istream& args) const;
	bool PrintFns(std::istream& args) const;
	bool DefineVar(std::istream& args);
	bool DefiningVarHandle(std::string name);
	bool DefineFn(std::istream& args);
	bool LetVar(std::istream& args);
	bool Print(std::istream& args) const;
	bool ParseLetExpression(std::string exp, std::string& leftOperand, std::string& rightOperand) const;
	bool ParseFnExpression(std::string exp, std::string& name, std::string& leftOperand, std::string& operation, std::string& rightOperand) const;
	bool IsIdentifierValid(std::string ident) const;
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};