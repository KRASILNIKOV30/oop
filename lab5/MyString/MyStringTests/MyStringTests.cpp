#include "../MyString/CMyString.h"
#include "../../../external/catch2/catch.hpp"

SCENARIO("My string constructing")
{
	WHEN("Construct my string without any params")
	{
		CMyString str;

		THEN("my string has zero length")
		{
			CHECK(str.GetLength() == 0);
			CHECK(strcmp(str.GetStringData(), "") == 0);
		}
	}

	WHEN("Constructing my string by another string")
	{
		CMyString str("Hello");

		THEN("my string is equal to 'Hello'")
		{
			CHECK(str.GetLength() == 5);
			CHECK(strcmp(str.GetStringData(), "Hello") == 0);
		}
	}

	WHEN("Constructing my string by chars array")
	{
		CMyString str("Hello world", 5);

		THEN("my string is equal to 'Hello'")
		{
			CHECK(str.GetLength() == 5);
			CHECK(strcmp(str.GetStringData(), "Hello") == 0);
		}
	}

	WHEN("Constructing my string by stlString")
	{
		std::string stlStr("Hello");
		CMyString str(stlStr);

		THEN("my string is equal to 'Hello'")
		{
			CHECK(str.GetLength() == 5);
			CHECK(strcmp(str.GetStringData(), "Hello") == 0);
		}
	}

	WHEN("Constructing my string by another my string")
	{
		CMyString str("Hello");
		CMyString copy(str);

		THEN("copy is equal to 'Hello'")
		{
			CHECK(copy.GetLength() == 5);
			CHECK(strcmp(copy.GetStringData(), "Hello") == 0);
		}
	}

	WHEN("Constructing my string by move constructor")
	{
		CMyString str(std::move(CMyString("Hello")));

		THEN("copy is equal to 'Hello'")
		{
			CHECK(str.GetLength() == 5);
			CHECK(strcmp(str.GetStringData(), "Hello") == 0);
		}
	}
}

SCENARIO("My string clearing")
{
	GIVEN("Not empty string")
	{
		CMyString str("Hello");

		WHEN("Clear my string")
		{
			str.Clear();

			THEN("My string has zero length")
			{
				CHECK(str.GetLength() == 0);
				CHECK(strcmp(str.GetStringData(), "") == 0);
			}
		}
	}
}

SCENARIO("Substring getting")
{
	GIVEN("My string 'Hello world'")
	{
		CMyString str("Hello big world");

		WHEN("Take substring from middle with a length less than the rest of the string")
		{
			CMyString substr = str.SubString(6, 8);

			THEN("Get substr from middle")
			{
				CHECK(substr.GetLength() == 8);
				CHECK(strcmp(substr.GetStringData(), "big worl") == 0);
			}
		}

		WHEN("Take substring from middle with a length equal to the rest of the string")
		{
			CMyString substr = str.SubString(6, 9);

			THEN("Get substr from middle")
			{
				CHECK(substr.GetLength() == 9);
				CHECK(strcmp(substr.GetStringData(), "big world") == 0);
			}
		}

		WHEN("Take substring from middle with a length bigger than the rest of the string")
		{
			CMyString substr = str.SubString(6, 10);

			THEN("Get substr from middle")
			{
				CHECK(substr.GetLength() == 9);
				CHECK(strcmp(substr.GetStringData(), "big world") == 0);
			}
		}

		WHEN("Take substring from middle without length")
		{
			CMyString substr = str.SubString(6, 10);

			THEN("Get substr from middle to end of my string")
			{
				CHECK(substr.GetLength() == 9);
				CHECK(strcmp(substr.GetStringData(), "big world") == 0);
			}
		}
	}
}
