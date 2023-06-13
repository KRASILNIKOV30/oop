#pragma once
#include <string>

struct StackNode
{
	std::string value;
	StackNode* next;
};

class CStringStack
{
public:
	CStringStack() = default;
	bool IsEmpty() const;
	std::string& GetTop() const;
	void Push(std::string value);
	void Pop();
	int GetSize() const;
	~CStringStack();
	CStringStack(CStringStack const& other);
	CStringStack(CStringStack&& other) noexcept;
	CStringStack& operator=(CStringStack const& other);
	CStringStack& operator=(CStringStack&& other) noexcept;

private:
	StackNode* m_top = nullptr;
	//добавить размер
	int m_size = 0;
};

