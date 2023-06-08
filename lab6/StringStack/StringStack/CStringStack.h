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
	~CStringStack();
	CStringStack(CStringStack const& other);
	CStringStack(CStringStack&& other) noexcept;
	CStringStack& operator=(CStringStack const&) = delete;
	CStringStack& operator=(CStringStack&& other);

private:
	StackNode* m_top = nullptr;
	//добавить размер
};

