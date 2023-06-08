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

		CMyString zeroCodeStr("Hello\0World", 11);

		THEN("My string is equal to 'HelloWorld' with zero code char in the middle")
		{
			CHECK(zeroCodeStr.GetLength() == 11);
			CHECK(std::equal(zeroCodeStr.GetStringData(), zeroCodeStr.GetStringData() + zeroCodeStr.GetLength(), "Hello\0World"));
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

		std::string zeroCodeStlString("Hello\0World", 11);
		CMyString zeroCodeStr(zeroCodeStlString);

		THEN("my string is equal to 'HelloWorld' with zero code char in the middle")
		{
			CHECK(zeroCodeStr.GetLength() == 11);
			CHECK(std::equal(zeroCodeStr.GetStringData(), zeroCodeStr.GetStringData() + zeroCodeStr.GetLength(), "Hello\0World"));
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

		CMyString zeroCodeStr("Hello\0World", 11);
		CMyString zeroCodeCopy(zeroCodeStr);
		THEN("copy is equal to 'HelloWorld' with zero code char in the middle")
		{
			CHECK(zeroCodeCopy.GetLength() == 11);
			CHECK(std::equal(zeroCodeCopy.GetStringData(), zeroCodeCopy.GetStringData() + zeroCodeCopy.GetLength(), "Hello\0World"));
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

TEST_CASE("Getting substring with start index greater than string length")
{
	CMyString str("Hello world");
	CHECK_THROWS_AS(str.SubString(11, 1), std::logic_error);
	CHECK_THROWS_AS(str.SubString(12, 1), std::logic_error);
}

TEST_CASE("Check opertor =")
{
	CMyString str;

	str = CMyString("My string");
	CHECK(strcmp(str.GetStringData(), "My string") == 0);

	str = "Some chars";
	CHECK(strcmp(str.GetStringData(), "Some chars") == 0);

	str = std::string("STL string");
	CHECK(strcmp(str.GetStringData(), "STL string") == 0);

	str = str;
	CHECK(strcmp(str.GetStringData(), "STL string") == 0);

	str = std::move(str);
	CHECK(strcmp(str.GetStringData(), "STL string") == 0);

	CMyString strToMove("Move");
	str = std::move(strToMove);
	CHECK(strcmp(str.GetStringData(), "Move") == 0);
}

TEST_CASE("Check operator +")
{
	CMyString str("World");

	CMyString result = CMyString("Hello") + str;
	CHECK(strcmp(result.GetStringData(), "HelloWorld") == 0);

	result = std::string("Hello") + str;
	CHECK(strcmp(result.GetStringData(), "HelloWorld") == 0);

	result = "Hello" + str;
	CHECK(strcmp(result.GetStringData(), "HelloWorld") == 0);
}

TEST_CASE("Check operator +=")
{
	CMyString str("Hello");
	CHECK(std::addressof(str += CMyString("World")) == std::addressof(str));
	CHECK(strcmp(str.GetStringData(), "HelloWorld") == 0);
}

TEST_CASE("Check operator ==")
{
	CMyString str("Hello");
	CHECK(str == CMyString("Hello"));
	CHECK_FALSE(str == CMyString("Helloo"));
	CHECK_FALSE(str == CMyString("hello"));
	CHECK(CMyString("") == CMyString(""));
}

TEST_CASE("Check operator !=")
{
	CMyString str("Hello");
	CHECK_FALSE(str != CMyString("Hello"));
	CHECK(str != CMyString("Helloo"));
	CHECK(str != CMyString("hello"));
	CHECK_FALSE(CMyString("") != CMyString(""));
}

TEST_CASE("Check operator >, <, >=, <=")
{
	CMyString str("Hello");

	CHECK(str > CMyString("Hell"));
	CHECK_FALSE(str > CMyString("Hello"));
	
	CHECK(str < CMyString("World"));
	CHECK_FALSE(str < CMyString("Apple"));

	CHECK(str >= CMyString("Hello"));
	CHECK_FALSE(str >= CMyString("World"));

	CHECK(str <= CMyString("Helloa"));
	CHECK_FALSE(str <= CMyString("Apple"));
}

TEST_CASE("Check operator []")
{
	CMyString str("My string");
	const CMyString constStr("Const my string");

	CHECK(str[1] == 'y');
	CHECK(constStr[1] == 'o');

	str[8] = 'k';
	CHECK(strcmp(str.GetStringData(), "My strink") == 0);

	CHECK_THROWS_AS(str[9], std::out_of_range);
	CHECK_THROWS_AS(str[10], std::out_of_range);
	CHECK_THROWS_AS(constStr[15], std::out_of_range);
	CHECK_THROWS_AS(constStr[16], std::out_of_range);
}

TEST_CASE("Check operator >> and <<")
{
	CMyString strOut("My string");
	CMyString strIn;
	std::stringstream stream = std::stringstream();
	stream << strOut;
	CHECK(stream.str() == "My string");
	stream >> strIn;
	CHECK(strcmp(strIn.GetStringData(), "My") == 0);
}