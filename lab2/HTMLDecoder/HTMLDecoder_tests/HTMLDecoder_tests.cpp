#include <iostream>
#include "../HTMLDecoder/HTMLDecode.h"
#include "../../../external/catch2/catch.hpp"

TEST_CASE("Text with html-entities")
{
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M’s");
}

TEST_CASE("Incorrect html-entities")
{
	REQUIRE(HtmlDecode("Cat <says> ""Meow"". M&M’s ") == "Cat <says> ""Meow"". M&M’s ");
}

TEST_CASE("Only html-entities")
{
	REQUIRE(HtmlDecode("&quot;&apos;&lt;&gt;&amp;") == "\"’<>&");
}

TEST_CASE("Empty input")
{
	REQUIRE(HtmlDecode("").empty());
}


TEST_CASE("composite html entity")
{
    REQUIRE(HtmlDecode(" &amp;lt;&hello ") == " &lt;&hello ");
}

TEST_CASE("Long html entity")
{
    REQUIRE(HtmlDecode("hello&hello;hello") == "hello&hello;hello");
}