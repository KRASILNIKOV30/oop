#include <iostream>
#include <string>
#include "../URLParser/ParseURL.h"

namespace
{
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
}

int main() 
{
    std::string url;
    while (std::getline(std::cin, url)) {
		if (ParseURL(url, protocol, port, host, document)) {
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			std::cout << "DOC: " << document << std::endl;
		}
		else {
			std::cout << "Url not found" << std::endl;
		}
    }
}