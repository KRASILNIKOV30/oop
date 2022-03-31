#include <string>
#include <iostream>
#include "HTMLDecode.h"

std::string SpecialChDef(std::string htmlEntity)
{
	if (htmlEntity == "&quot") { return """"; }
	if (htmlEntity == "&apos") { return "''"; }
	if (htmlEntity == "&lt") { return "<"; }
	if (htmlEntity == "&gt") { return ">"; }
	if (htmlEntity == "&amp") { return "amp"; }
	return "0";
}

std::string HtmlDecode(std::string const& html)
{
	std::string text = html;
	std::string specialCh = "";
	std::string htmlEntity = "";
	for (int index = 0; index != -1 && text[index] != '\0'; index++)
	{
		std::cout << index << std::endl;
		index = text.find("&", index);
		std::cout << index << std::endl;
		if (index != -1)
		{
			//std::cout << index << " " << html[index] << std::endl;
			int i = index;
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