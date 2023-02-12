#include <string>
#include "HTMLDecode.h"
#include <map>
const int HTML_ENTITY_MAX_LENGTH = 6;

short GetHtmlEntityLength(size_t startIndex, const std::string& text)
{
    size_t i = startIndex;
    short result = 0;
    while (text[i] != ';' and result <= HTML_ENTITY_MAX_LENGTH)
    {
        result = i - startIndex + 1;
        i++;
    }
    return result;
}

std::string HtmlDecode(std::string const& text)
{
	std::map<std::string, std::string> htmlEntities =
	{
		{"&quot", "\""},
		{"&apos", "’"},
		{"&lt", "<"},
		{"&gt", ">"},
		{"&amp", "&"}
	};
    std::string_view htmlEntity;
    std::map<std::string, std::string>::iterator iterator;
	size_t index = 0;
    size_t i;
    std::string result;

    while (index < text.length())
    {
        if (text[index] == '&')
        {
            htmlEntity = text.substr(index, GetHtmlEntityLength(index, text));
            iterator = htmlEntities.find({htmlEntity.begin(), htmlEntity.end()});
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