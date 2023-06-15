#include "../../../external/catch2/catch.hpp"
#include "../MyList/CMyList.h"
#include <iostream>

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
			auto it = list.Begin();

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

		WHEN("Get begin iterator")
		{
			auto it = list.End();

			THEN("Iterator points to element following the last")
			{
				CHECK(*(--it) == "C");
			}
		}
	}
}