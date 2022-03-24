
#include <string>
#include <iostream>
#include "HTMLDecode.h"

std::string HtmlDecode(std::string const& html)
{
	int index = 0;
	while (html[index] != '\0')
	{
		index = html.find("&", index);
		if (index != std::string::npos)
		{
			std::string htmlEntity = "";
			while (html[index] != ';' && html[index] != '\0')
			{
				htmlEntity.push_back(html[index]);
				index++;
			}
			return htmlEntity;
		};
		return "HTML-entity was not found";
	}
}