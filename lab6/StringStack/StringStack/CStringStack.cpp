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
    StackNode* top = new StackNode{value, m_top};
    m_top = top;
    m_size++;
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
    m_size--;
}

int CStringStack::GetSize() const
{
    return m_size;
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
    m_size = other.m_size;
    auto othersNode = other.m_top;
    m_top = new StackNode{ othersNode->value, nullptr };
    auto prev = m_top;
    while (othersNode->next != nullptr)
    {
        othersNode = othersNode->next;
        prev->next = new StackNode{ othersNode->value, nullptr };
        prev = prev->next;
    }
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    : m_top(other.m_top)
    , m_size(other.m_size)
{
    other.m_top = nullptr;
    other.m_size = 0;
}

CStringStack& CStringStack::operator=(CStringStack const& other)
{
    return *this = std::move(CStringStack(other));
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
    m_top = other.m_top;
    m_size = other.m_size;
    other.m_top = nullptr;
    other.m_size = 0;
    return *this;
}
