#include <string>
#include <iostream>
#include "HTMLDecode.h"

std::string SpecialChDef(std::string htmlEntity)
{
	if (htmlEntity == "&quot") { return "\""; }
	if (htmlEntity == "&apos") { return "’"; }
	if (htmlEntity == "&lt") { return "<"; }
	if (htmlEntity == "&gt") { return ">"; }
	if (htmlEntity == "&amp") { return "&"; }
	return "0";
}

std::string HtmlDecode(std::string const& html)
{
	std::string text = html;
	std::string specialCh = "";
	for (int index = 0; index != -1; index++)
	{
		index = text.find("&", index);
		if (index != -1)
		{
			int i = index;
			std::string htmlEntity = "";
			while (text[i] != ';' && text[i] != '\0')
			{
				htmlEntity.push_back(text[i]);
				i++;
			}
			if (text[i] == ';')
			{
				specialCh = SpecialChDef(htmlEntity);
				if (specialCh != "0")
				{
					text.replace(index, htmlEntity.size() + 1, specialCh);
				}
			}
		}
		else
		{
			break;
		}
	}
	return text;
}