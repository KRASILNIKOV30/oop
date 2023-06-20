#include "../../../external/catch2/catch.hpp"
#include "../MyList/CMyList.h"
#include <iostream>
#include <list>

SCENARIO("Basic list behavior")
{
	GIVEN("Empty list of strings")
	{
		CMyList<std::string> list;
		CHECK(list.IsEmpty());
		CHECK(list.GetSize() == 0);

		WHEN("Push one value to list")
		{
			list.PushBack("world");

			THEN("List has one value")
			{
				CHECK_FALSE(list.IsEmpty());
				CHECK(list.GetSize() == 1);
				CHECK(list.GetFirst() == "world");
				CHECK(list.GetLast() == "world");
			}

			AND_WHEN("Push the second value to front")
			{
				list.PushFront("hello");

				THEN("Value adds to first position of the list")
				{
					CHECK(list.GetSize() == 2);
					CHECK(list.GetFirst() == "hello");
					CHECK(list.GetLast() == "world");
				}
			}

			AND_WHEN("Push the second value to back")
			{
				list.PushBack("hello");

				THEN("Value adds to last position of the list")
				{
					CHECK(list.GetSize() == 2);
					CHECK(list.GetFirst() == "world");
					CHECK(list.GetLast() == "hello");
				}
			}
		}
	}
}

SCENARIO("Iterator test")
{
	GIVEN("List with three strings")
	{
		CMyList<std::string> list;
		list.PushBack("A");
		list.PushBack("B");
		list.PushBack("C");

		WHEN("Get begin iterator")
		{
			auto it = list.begin();

			THEN("Iterator points to first element")
			{
				CHECK(*it == "A");
			}

			THEN("Can sort out elements of list by forward direction")
			{
				CHECK(*(++it) == "B");
				CHECK(*(++it) == "C");

				AND_THEN("Can sort out elements of list by backward direction")
				{
					CHECK(*(--it) == "B");
					CHECK(*(--it) == "A");
				}
			}
		}

		WHEN("Get end iterator")
		{
			auto it = list.end();

			THEN("Iterator points to element following the last")
			{
				CHECK(*(--it) == "C");
			}
		}
	}
}

SCENARIO("Reverce iterator test")
{
	GIVEN("List with three strings")
	{
		CMyList<std::string> list;
		list.PushBack("A");
		list.PushBack("B");
		list.PushBack("C");

		std::list<std::string> l;
		l.push_back("A");
		l.push_back("B");
		l.erase(l.begin());

		auto it = l.begin();

		WHEN("Get reverse iterator to begin")
		{
			auto it = list.rbegin();

			THEN("Iterator points to first element")
			{
				CHECK(*it == "C");

				THEN("Can sort out elements of list by backward direction")
				{
					CHECK(*(++it) == "B");
					CHECK(*(++it) == "A");

					AND_THEN("Can sort out elements of list by forward direction")
					{
						CHECK(*(--it) == "B");
						CHECK(*(--it) == "C");
					}
				}
			}
		}

		WHEN("Get reverse iterator to end")
		{
			auto it = list.rend();

			THEN("Iterator points to element following the last")
			{
				CHECK(*(--it) == "A");
			}
		}
	}
}

SCENARIO("Erase element from list")
{
	GIVEN("List with three strings")
	{
		CMyList<std::string> list;
		list.PushBack("A");
		list.PushBack("B");
		list.PushBack("C");

		WHEN("Erase element from the middle of the list")
		{
			auto it = list.begin();
			it = list.Erase(++it);

			THEN("Element erased and list contains two elements")
			{
				CHECK(list.GetSize() == 2);
				CHECK(list.GetFirst() == "A");
				CHECK(list.GetLast() == "C");
				CHECK(*it == "C");
			}
		}

		WHEN("Erase the first element")
		{
			auto it = list.Erase(list.begin());

			THEN("Element erased and list contaons two elements")
			{
				CHECK(list.GetSize() == 2);
				CHECK(list.GetFirst() == "B");
				CHECK(list.GetLast() == "C");
				CHECK(it == list.begin());
			}
		}

		WHEN("Erase the last element")
		{
			auto it = list.Erase(--list.end());

			THEN("Element erased and list contaons two elements")
			{
				CHECK(list.GetSize() == 2);
				CHECK(list.GetFirst() == "A");
				CHECK(list.GetLast() == "B");
				CHECK(it == list.end());
			}
		}

		WHEN("Erase element from list with size 1")
		{
			list.Erase(--list.end());
			auto it = list.Erase(list.begin());
			CHECK(list.GetSize() == 1);
			list.Erase(it);

			THEN("List is empty")
			{
				CHECK(list.IsEmpty());
			}
		}
	}
}

SCENARIO("Insert element to list")
{
	GIVEN("Empty list")
	{
		CMyList<std::string> list;

		WHEN("Insert element at the begin")
		{
			auto it = list.Insert(list.begin(), "A");

			THEN("List contains one element")
			{
				CHECK(list.GetSize() == 1);
				CHECK(list.GetFirst() == "A");
				CHECK(list.GetLast() == "A");
				CHECK(it == list.begin());
			}

			AND_WHEN("Insert element at the end")
			{
				it = list.Insert(list.end(), "C");

				THEN("List contains two elements")
				{
					CHECK(list.GetSize() == 2);
					CHECK(list.GetFirst() == "A");
					CHECK(list.GetLast() == "C");
					CHECK(*it == "C");
				}

				AND_WHEN("Insert element at the middle")
				{
					it = list.Insert(it, "B");

					THEN("List contains two elements")
					{
						CHECK(list.GetSize() == 3);
						CHECK(list.GetFirst() == "A");
						CHECK(list.GetLast() == "C");
						CHECK(*it == "B");
					}
				}
			}
		}
	}
}

