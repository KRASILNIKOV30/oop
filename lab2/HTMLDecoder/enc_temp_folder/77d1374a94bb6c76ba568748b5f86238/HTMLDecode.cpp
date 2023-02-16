#include <string>
#include "HTMLDecode.h"
#include <map>
#include <iostream>

namespace {
	const int HTML_ENTITY_MAX_LENGTH = 4;

	size_t GetHtmlEntityLength(size_t startIndex, const std::string_view& text)
	{
		size_t i = startIndex;
		while (i - startIndex <= HTML_ENTITY_MAX_LENGTH && i < text.length() && text[i] != ';')
		{
			i++;
		}
		return i - startIndex;
	}

	const std::map<std::string, std::string> htmlEntities =
	{
		{"&quot", "\""},
		{"&apos", "'"},
		{"&lt", "<"},
		{"&gt", ">"},
		{"&amp", "&"}
	};
}


std::string HtmlDecode(std::string_view text)
{
	std::string_view htmlEntity;
	std::map<std::string, std::string>::const_iterator iterator;
	size_t index = 0;
	std::string result;

	while (index < text.length())
	{
		if (text[index] == '&')
		{
			htmlEntity = text.substr(index, GetHtmlEntityLength(index, text));
			iterator = htmlEntities.find({ htmlEntity.begin(), htmlEntity.end() });
			if (iterator != htmlEntities.end())
			{
				result.append(iterator->second);
				index += htmlEntity.length() + 1;
			}
			else
			{
				result.append(htmlEntity);
				index += htmlEntity.length();
			}
		}
		else
		{
			result.push_back(text[index]);
			index++;
		}
	}

	return result;
}