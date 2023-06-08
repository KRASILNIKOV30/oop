#include "CStringStack.h"
#include <stdexcept>

bool CStringStack::IsEmpty() const
{
    return m_top == nullptr;
}

std::string& CStringStack::GetTop() const
{
    if (IsEmpty())
    {
        throw std::logic_error("Stack is empty");
    }

    return m_top->value;
}

void CStringStack::Push(std::string value)
{
    //утечка пам€ти (при присваивании строки) (»справлено)
    StackNode* top = new StackNode;
    top->next = m_top;
    top->value = std::move(value);
    m_top = top;
}

void CStringStack::Pop()
{
    if (IsEmpty())
    {
        throw std::logic_error("Stack is empty");
    }
    StackNode* top = m_top;
    m_top = m_top->next;
    delete top;
}

CStringStack::~CStringStack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

CStringStack::CStringStack(CStringStack const& other)
{
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    :m_top(other.m_top)
{
    other.m_top = nullptr;
}

CStringStack& CStringStack::operator=(CStringStack&& other)
{
    return *this;
}
