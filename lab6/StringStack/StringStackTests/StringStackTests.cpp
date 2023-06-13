#include "../../../external/catch2/catch.hpp"
#include "../StringStack/CStringStack.h"

SCENARIO("Stack test")
{
	GIVEN("Empty string stack")
	{
		CStringStack stack;
		CHECK(stack.IsEmpty());
		CHECK(stack.GetSize() == 0);
		
		WHEN("Push 'Hello' into stack")
		{
			stack.Push("Hello");

			THEN("Stack is not empty and contains 'Hello'")
			{
				CHECK_FALSE(stack.IsEmpty());
				CHECK(stack.GetSize() == 1);
				CHECK(stack.GetTop() == "Hello");
			}

			AND_WHEN("Add the second string 'World' into stack")
			{
				stack.Push("World");

				THEN("Stack is not empty and constains 'World' at the top")
				{
					CHECK_FALSE(stack.IsEmpty());
					CHECK(stack.GetSize() == 2);
					CHECK(stack.GetTop() == "World");
				}

				AND_WHEN("Pop value from stack")
				{
					stack.Pop();

					THEN("Stack is not empty and contains 'Hello' at the top")
					{
						CHECK_FALSE(stack.IsEmpty());
						CHECK(stack.GetSize() == 1);
						CHECK(stack.GetTop() == "Hello");
					}

					AND_WHEN("Pop value from stack again")
					{
						stack.Pop();

						THEN("Stack is empty")
						{
							CHECK(stack.IsEmpty());
							CHECK(stack.GetSize() == 0);
						}
					}
				}
			}
		}
	}
}

SCENARIO("Stack copying")
{
	GIVEN("Stack with three values")
	{
		CStringStack stack;
		stack.Push("A");
		stack.Push("B");
		stack.Push("C");

		WHEN("Create copy of this stack by moving constructor")
		{
			CStringStack stackCopy(std::move(stack));

			THEN("Copy has the same number of values")
			{
				CHECK_FALSE(stackCopy.IsEmpty());
				CHECK(stackCopy.GetSize() == 3);
			}

			AND_THEN("Copy has the same values")
			{
				CHECK(stackCopy.GetTop() == "C");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "B");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "A");
				stackCopy.Pop();
				CHECK(stackCopy.IsEmpty());
			}
		}

		WHEN("Create copy of this stack by copying constructor")
		{
			CStringStack stackCopy(stack);

			THEN("Copy has the same number of values")
			{
				CHECK_FALSE(stackCopy.IsEmpty());
				CHECK(stackCopy.GetSize() == 3);
			}

			AND_THEN("Copy has the same values")
			{
				CHECK(stackCopy.GetTop() == "C");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "B");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "A");
				stackCopy.Pop();
				CHECK(stackCopy.IsEmpty());
			}
		}

		WHEN("Create copy of this stack by operator =")
		{
			CStringStack stackCopy;
			stackCopy = stack;

			THEN("Copy has the same number of values")
			{
				CHECK_FALSE(stackCopy.IsEmpty());
				CHECK(stackCopy.GetSize() == 3);
			}

			AND_THEN("Copy has the same values")
			{
				CHECK(stackCopy.GetTop() == "C");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "B");
				stackCopy.Pop();
				CHECK(stackCopy.GetTop() == "A");
				stackCopy.Pop();
				CHECK(stackCopy.IsEmpty());
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