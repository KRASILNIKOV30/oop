#include "../../../external/catch2/catch.hpp"
#include "../ExpandTemplate/ExpandTemplate.h"

SCENARIO("Expand template tests")
{
	GIVEN("Empty template and no params")
	{
		std::string tpl;
		TemplateParams params;

		THEN("Expanded template is empty")
		{
			CHECK(ExpandTemplate(tpl, params).empty());
		}
	}

	GIVEN("Not empty template without params")
	{
		std::string tpl = "Hello %NAME%";
		TemplateParams params;

		THEN("Expanded template is equal to initial template")
		{
			CHECK(ExpandTemplate(tpl, params) == tpl);
		}
	}

	GIVEN("Not empty template with params that does not exist in template")
	{
		std::string tpl = "Hello %NAME%";
		TemplateParams params = { 
			{"%SURNAME%", "Ivanov"} 
		};

		THEN("Expanded template is equal to initial template")
		{
			CHECK(ExpandTemplate(tpl, params) == tpl);
		}
	}

	GIVEN("Template is equal to param")
	{
		std::string tpl = "%NAME%";
		TemplateParams params = { 
			{"%NAME%", "Bogdan"} 
		};

		THEN("Expanded template is equal to initial template")
		{
			CHECK(ExpandTemplate(tpl, params) == "Bogdan");
		}
	}

	GIVEN("Template consists only of parameters")
	{
		std::string tpl = "%NAME%%NAME%%DATE%";
		TemplateParams params = {
			{"%NAME%", "Bogdan"},
			{"%DATE%", "30"}
		};

		THEN("Template is expanded")
		{
			CHECK(ExpandTemplate(tpl, params) == "BogdanBogdan30");
		}
	}

	GIVEN("Template contains several parameters")
	{
		std::string tpl = "Hello, %USER_NAME%! Today is {WEEK_DAY}.";
		TemplateParams params = {
			{"%USER_NAME%", "Bogdan"},
			{"{WEEK_DAY}", "Saturday"}
		};

		THEN("Template is expanded")
		{
			CHECK(ExpandTemplate(tpl, params) == "Hello, Bogdan! Today is Saturday.");
		}
	}

	GIVEN("Template parameter values contain template parameters")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		TemplateParams params = {
			{"%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}"},
			{"{WEEK_DAY}", "Saturday. {WEEK_DAY}"}
		};

		THEN("Expanded template contains template parameters")
		{
			CHECK(ExpandTemplate(tpl, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Saturday. {WEEK_DAY}.");
		}
	}

	GIVEN("Parameter prefix is also a parameter")
	{
		std::string tpl = "AAA";
		TemplateParams params = {
			{"A", "[a]"},
			{"AA", "[aa]"},
		};

		THEN("Parameter with the longest length is substituted")
		{
			CHECK(ExpandTemplate(tpl, params) == "[aa][a]");
		}
	}

	GIVEN("Parameter prefix is also a parameter (extended)")
	{
		std::string tpl = "-AABBCCCCCABC+";
		TemplateParams params = {
			{"A", "[a]"},
			{"AA", "[aa]"},
			{"B", "[b]"},
			{"BB", "[bb]"},
			{"C", "[c]"},
			{"CC", "[cc]"},
		};

		THEN("Parameter with the longest length is substituted")
		{
			CHECK(ExpandTemplate(tpl, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
		}
	}

	GIVEN("The prefix of one parameter is the suffix of another")
	{
		std::string tpl = "-ABCED+";
		TemplateParams params = {
			{"ABCD", "[abcd]"},
			{"BCE", "[bce]"},
		};

		THEN("Template was expanded correctly after follow the suffix link")
		{
			CHECK(ExpandTemplate(tpl, params) == "-A[bce]D+");
		}
	}
}