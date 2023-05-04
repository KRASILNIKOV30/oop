#pragma once
#include "Var.h"
//������ include (����������)
#include <string>
#include <vector>
#include "Memory.h"
#include <memory>
#include <optional>

class Function
{
public:
	Function
	(
		std::string name,
		std::vector<std::string> lexemes,
		std::shared_ptr<Memory> memory
	);
	std::string GetName() const;
	std::vector<std::string> GetLexemes() const;
	double GetValue() const;
	//���������� �� ��������� ������������ (����������)
private:
	std::string m_name;
	std::vector<std::string> m_lexemes;
	//����� ����� ��������� (����������)
	std::shared_ptr<Memory> m_memory;
};