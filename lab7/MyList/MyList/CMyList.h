#include <iterator>
#include <new>
#include <memory>

template<typename T>
struct ListNode
{
	T value;
	ListNode* prev;
	ListNode* next;
};

template <typename T>
struct Node
{
	template <typename TT>
	void Construct(TT&& value)
	{
		std::construct_at(Get(), std::forward<TT>(value));
	}

	void Destroy()
	{
		std::destroy_at(Get());
	}

	T* Get()
	{
		return reinterpret_cast<T*>(raw);
	}

	alignas(T) char raw[sizeof(t)];
};

template<typename T>
class CMyList
{
public:
	class iterator : public std::iterator<std::bidirectional_iterator_tag, T, T, const T*, T>
	{
	public:
		iterator(ListNode<T>* node, bool isEnd = false) 
			: m_pNode(node)
			, m_isEnd(isEnd)
		{}

		iterator& operator++() 
		{
			if (m_pNode->next == nullptr)
			{
				m_isEnd = true;
			}
			else
			{
				m_pNode = m_pNode->next;
			}
			return *this;
		}

		iterator operator++(int) 
		{ 
			iterator retval = *this;
			++(*this);
			return retval;
		}

		iterator& operator--() 
		{ 
			if (m_isEnd)
			{
				m_isEnd = false;
			}
			else
			{
				m_pNode = m_pNode->prev;
			}
			return *this;
		}

		iterator operator--(int)
		{
			iterator retval = *this;
			--(*this);
			return retval;
		}

		bool operator==(iterator other) const 
		{ 
			return (m_pNode == other.m_pNode) && (m_isEnd == other.m_isEnd);
		}

		bool operator!=(iterator other) const 
		{ 
			return !(*this == other); 
		}

		T& operator*() const 
		{ 
			return m_pNode->value;
		}

		ListNode<T>* GetNode() const
		{
			return m_pNode;
		}

	private:
		ListNode<T>* m_pNode;
		bool m_isEnd;
	};

	//с маленькой буквы
	//Добавить константные итераторы
	iterator Begin()
	{
		return iterator(m_pFirst);
	}

	iterator End()
	{
		return iterator(m_pLast, true);
	}

	std::reverse_iterator<iterator> RBegin()
	{
		return std::reverse_iterator<iterator>(End());
	}

	std::reverse_iterator<iterator> REnd()
	{
		return std::reverse_iterator<iterator>(Begin());
	}

	bool IsEmpty() const;
	int GetSize() const;
	void PushBack(T const& value);
	void PushFront(T const& value);
	T& GetFirst() const;
	T& GetLast() const;
	//const iterator
	iterator Erase(iterator iter)
	{
		ListNode<T>* node = iter.GetNode();
		ListNode<T>* result = node->next;
		bool isEnd = false;
		if (node->prev != nullptr)
		{
			node->prev->next = node->next;
		}
		else
		{
			m_pFirst = node->next;
		}
		if (node->next != nullptr)
		{
			node->next->prev = node->prev;
		}
		else
		{
			m_pLast = node->prev;
			result = node->prev;
			isEnd = true;
		}
		delete node;
		m_size--;

		return iterator(result, isEnd);
	}

	//const iterator
	iterator Insert(iterator iter, T const& value)
	{
		if (iter == End())
		{
			PushBack(value);
			return --End();
		}
		if (iter == Begin())
		{
			PushFront(value);
			return Begin();
		}
		ListNode<T>* node = iter.GetNode();
		ListNode<T>* newNode = new ListNode<T>{ value, node->prev, node };
		node->prev->next = newNode;
		node->prev = newNode;
		m_size++;

		return iterator(newNode);
	}
	
private:
	ListNode<T>* m_pFirst = nullptr;
	ListNode<T>* m_pLast = nullptr;
	int m_size = 0;
};

template<typename T>
inline bool CMyList<T>::IsEmpty() const
{
	return m_size == 0;
}

template<typename T>
inline int CMyList<T>::GetSize() const
{
	return m_size;
}

template<typename T>
inline void CMyList<T>::PushBack(T const& value)
{
	ListNode<T>* last = new ListNode<T>{ value, m_pLast, nullptr };
	m_pLast = last;
	m_size++;
	if (GetSize() == 1)
	{
		m_pFirst = m_pLast;
	}
	else
	{
		m_pLast->prev->next = m_pLast;
	}
}

template<typename T>
inline void CMyList<T>::PushFront(T const& value)
{
	ListNode<T>* first = new ListNode<T>{ value, nullptr, m_pFirst };
	m_pFirst = first;
	m_size++;
	if (GetSize() == 1)
	{
		m_pLast = m_pFirst;
	}
	else
	{
		m_pFirst->next->prev = m_pFirst;
	}
}

template<typename T>
inline T& CMyList<T>::GetFirst() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("List is empty");
	}
	return m_pFirst->value;
}

template<typename T>
inline T& CMyList<T>::GetLast() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("List is empty");
	}
	return m_pLast->value;
}