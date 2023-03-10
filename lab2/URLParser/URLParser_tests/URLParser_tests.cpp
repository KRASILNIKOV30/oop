#include "../../../external/catch2/catch.hpp"
#include "../URLParser/ParseURL.h"
#include <string>

namespace
{
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
}

TEST_CASE("common url") {
	REQUIRE(ParseURL("https://localhost:8080/table", protocol, port, host, document));
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(host == "localhost");
	REQUIRE(port == 8080);
	REQUIRE(document == "table");

}

TEST_CASE("without port") {
	REQUIRE(ParseURL("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
	REQUIRE(protocol == Protocol::FTP);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(port == 21);
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("url with some text") {
	REQUIRE(!ParseURL("some text HTTPS://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
}

TEST_CASE("with empty port") {
	REQUIRE(!ParseURL("http:///www.mysite.com:/docs", protocol, port, host, document));
}

TEST_CASE("invalid url") {
	REQUIRE(!ParseURL("http:///www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
}

TEST_CASE("test port boundary values") {
	REQUIRE(!ParseURL("ftp://localhost:65536", protocol, port, host, document));
	REQUIRE(ParseURL("ftp://localhost:65535", protocol, port, host, document));
	REQUIRE(!ParseURL("ftp://localhost:0", protocol, port, host, document));
	REQUIRE(ParseURL("ftp://localhost:1", protocol, port, host, document));
}
