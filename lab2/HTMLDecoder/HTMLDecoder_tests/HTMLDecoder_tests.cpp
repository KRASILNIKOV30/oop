#include <iostream>
#include "../HTMLDecoder/HTMLDecode.h"
#include "../../../external/catch2/catch.hpp"

TEST_CASE("Correct input")
{
	REQUIRE(HtmlDecode("Cat &lt; says &gt; &quot; Meow &quot;.M &amp; M &apos; s") == "Cat <says> ""Meow"". M&M’s ");
}

//TEST_CASE("Input without html-entities")
//{
//	REQUIRE(HtmlDecode("Cat <says> ""Meow"". M&M’s ") == "HTML-entity was not found");
//}