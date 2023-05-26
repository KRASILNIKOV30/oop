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
			CHECK(str.GetStringData() == "");
		}
	}

	/*WHEN("Constructing my string by another string")
	{
		CMyString str("Hello");

		THEN("my string is equal to 'Hello'")
		{
			CHECK(str.GetLength() == 5);
			CHECK(str.GetStringData() == "Hello");
		}
	}*/
}
