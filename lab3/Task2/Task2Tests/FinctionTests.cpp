#include "../../../external/catch2/catch.hpp"
#include "../Task2/Function.h"

SCENARIO("Function declaration")
{
	GIVEN("Function named XPlusY")
	{
		Function function("XPlusY", 10.0);
		CHECK(function.GetName() == "XPlusY");
	}
}