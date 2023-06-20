#include <iterator>
#include <new>
#include <memory>

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

	alignas(T) char raw[sizeof(T)];
};

template<typename T>
struct ListNode
{
	ListNode* prev;
	ListNode* next;
	Node<T> value;
};

template<typename T>
class CMyList
{
public:
	class iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = T;
		using pointer = const T*;
		using reference = T;

		iterator(ListNode<T>* node) 
			: m_pNode(node)
		{}

		iterator& operator++() 
		{
			m_pNode = m_pNode->next;
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
			m_pNode = m_pNode->prev;
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
			return m_pNode == other.m_pNode;
		}

		bool operator!=(iterator other) const 
		{ 
			return !(*this == other); 
		}

		T& operator*() const 
		{ 
			return *m_pNode->value.Get();
		}

		ListNode<T>* GetNode() const
		{
			return m_pNode;
		}

	private:
		ListNode<T>* m_pNode;
	};

	//с маленькой буквы
	//Добавить константные итераторы
	iterator begin()
	{
		return iterator(m_pFirst);
	}

	iterator end()
	{
		return iterator(m_pSentinel);
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
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
		if (node->prev != nullptr)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		else
		{
			m_pFirst = node->next;
			node->next->prev = nullptr;
		}
		node->value.Destroy();
		delete node;
		m_size--;

		return iterator(result);
	}

	//const iterator
	iterator Insert(iterator iter, T const& value)
	{
		if (iter == end())
		{
			PushBack(value);
			return --end();
		}
		if (iter == begin())
		{
			PushFront(value);
			return begin();
		}
		ListNode<T>* node = iter.GetNode();
		ListNode<T>* newNode = new ListNode<T>{ node->prev, node };
		newNode->value.Construct(value);
		node->prev->next = newNode;
		node->prev = newNode;
		m_size++;

		return iterator(newNode);
	}
	
private:
	ListNode<T>* m_pSentinel = new ListNode{ m_pSentinel, m_pSentinel };
	ListNode<T>* m_pFirst = m_pSentinel;
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
	if (IsEmpty())
	{
		PushFront(value);
		return;
	}
	ListNode<T>* last = new ListNode<T>{ m_pSentinel->prev, m_pSentinel };
	last->value.Construct(value);
	m_pSentinel->prev->next = last;
	m_pSentinel->prev = last;
	m_size++;
}

template<typename T>
inline void CMyList<T>::PushFront(T const& value)
{
	ListNode<T>* first = new ListNode<T>{ nullptr, m_pFirst };
	first->value.Construct(value);
	m_pFirst = first;
	m_pFirst->next->prev = m_pFirst;
	m_size++;
}

template<typename T>
inline T& CMyList<T>::GetFirst() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("List is empty");
	}
	return *m_pFirst->value.Get();
}

template<typename T>
inline T& CMyList<T>::GetLast() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("List is empty");
	}
	return *m_pSentinel->prev->value.Get();
}