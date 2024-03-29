#include "../../../external/catch2/catch.hpp"
#include "../Task2/Memory.h"
#include "../Task2/Var.h"
#include "Common.h"

SCENARIO("Adding variable to memory")
{
	GIVEN("Empty memory")
	{
		Memory memory;

		THEN("Memory has no vars")
		{
			CHECK(memory.GetVars().size() == 0);
		}

		WHEN("I add var to memory")
		{
			memory.AddVar("x");

			THEN("Memory has one var")
			{
				REQUIRE(memory.GetVars().size() == 1);
			}
		}
	}
}

SCENARIO("Using variable from memory")
{
	GIVEN("Memory with one variable named x")
	{
		Memory memory;
		memory.AddVar("x");

		WHEN("I finding var named x")
		{
			auto memVar = memory.FindVar("x");

			THEN("Var is found")
			{
				REQUIRE(memVar.has_value());

				AND_THEN("Var has x name and NAN value")
				{
					CHECK(memVar.value().GetName() == "x");
					CHECK(isnan(memVar->GetValue()));
				}

				WHEN("I change value of variable")
				{
					memory.ChangeVarValue("x", 10);

					THEN("Var from memory change its value too")
					{
						CHECK(IsEquals(memory.FindVar("x")->GetValue(), 10));
					}
				}
			}
		}
	}
}