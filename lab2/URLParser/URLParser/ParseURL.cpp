#include <string>
#include <regex>
#include <iostream>

enum class Protocol 
{
	HTTP,
	HTTPS,
	FTP
};

namespace
{
	std::string StrToLower(std::string str) 
	{
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
		return str;
	}

	bool SetProtocol(Protocol& protocol, const std::string value) 
	{
		if (value == "http") {
			protocol = Protocol::HTTP;
		}
		else if (value == "https") {
			protocol = Protocol::HTTPS;
		} else if (value == "ftp") {
			protocol = Protocol::FTP;
		}
		else {
			return false;
		}
		return true;
	}

	bool SetDefaultPort(int& port, const Protocol protocol)
	{
		switch (protocol) {
		case Protocol::HTTP: {
			port = 80;
			return true;
		}
		case Protocol::HTTPS: {
			port = 443;
			return true;
		}
		case Protocol::FTP: {
			port = 21;
			return true;
		}
		default:
			return false;
		}
	}

	bool SetPort(int& port, const std::string value, const Protocol protocol)
	{
		if (value == "") {
			return SetDefaultPort(port, protocol);
		}
		if (port = stoi(value)) {
			return port >= 1 && port <= 65535;
		}
		return false;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document) 
{
	const std::regex reg(R"((http|https|ftp)://([\w.]+)(:(\d+))?(/(.*))?)", std::regex_constants::icase);
	std::smatch what;
	if (!std::regex_match(url, what, reg)) {
		return false;
	}
	if (!SetProtocol(protocol, StrToLower(what[1]))) {
		return false;
	}
	host = what[2];
	if (!SetPort(port, what[4], protocol)) {
		return false;
	}
	document = what[6];

	return true;
	
}