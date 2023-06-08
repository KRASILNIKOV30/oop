#include "../../../external/catch2/catch.hpp"
#include "../StringStack/CStringStack.h"

SCENARIO("Stack test")
{
	GIVEN("Empty string stack")
	{
		CStringStack stack;
		CHECK(stack.IsEmpty());
		
		WHEN("Push 'Hello' into stack")
		{
			stack.Push("Hello");

			THEN("Stack is not empty and contains 'Hello'")
			{
				CHECK_FALSE(stack.IsEmpty());
				CHECK(stack.GetTop() == "Hello");
			}

			AND_WHEN("Add the second string 'World' into stack")
			{
				stack.Push("World");

				THEN("Stack is not empty and constains 'World' at the top")
				{
					CHECK_FALSE(stack.IsEmpty());
					CHECK(stack.GetTop() == "World");
				}

				AND_WHEN("Pop value from stack")
				{
					stack.Pop();

					THEN("Stack is not empty and contains 'Hello' at the top")
					{
						CHECK_FALSE(stack.IsEmpty());
						CHECK(stack.GetTop() == "Hello");
					}

					AND_WHEN("Pop value from stack again")
					{
						stack.Pop();

						THEN("Stack is empty")
						{
							CHECK(stack.IsEmpty());
						}
					}
				}
			}
		}
	}
}

TEST_CASE("Incorrect actions with an empty stack")
{
	CStringStack stack;
	REQUIRE(stack.IsEmpty());
	CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
	CHECK_THROWS_AS(stack.Pop(), std::logic_error);
}