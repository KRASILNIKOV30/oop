#pragma once
#include <string>

enum class Protocol;
bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
