#include <string>
#include <iostream>
#include "HTMLDecode.h"
#include <map>

//именование с загл буквы
//передавать по константной ссылке строку и map
//заменить цикл на метод find
std::string getSpecialChDef(std::string htmlEntity, std::map<std::string, std::string> htmlEntities)
{
	for (auto& item: htmlEntities)
	{
		if (item.first == htmlEntity)
		{
			return item.second;
		}
	}
	//другой способ сообщения not found
	return "not found";
}

std::string HtmlDecode(std::string const& html)
{
	std::map<std::string, std::string> htmlEntities = 
	{
		{"&quot", "\""},
		{"&apos", "’"},
		{"&lt", "<"},
		{"&gt", ">"},
		{"&amp", "&"}
	};
	std::string text = html;
	std::string specialCh = "";
	bool isTextContainsHtmlEntities = true;
	//int мало надо size_t
	int index = 0;
	//код сложный
	//textContainsHtmlEntities
	while (isTextContainsHtmlEntities)
	{
		index = text.find("&", index);
		isTextContainsHtmlEntities = index != -1;
		if (isTextContainsHtmlEntities)
		{
			int i = index;
			std::string htmlEntity = "";
			//использовать string_view
			//по другому проверять конец строки
			while (text[i] != ';' && text[i] != '\0')
			{
				htmlEntity.push_back(text[i]);
				i++;
			};
			if (text[i] == ';')
			{
				specialCh = getSpecialChDef(htmlEntity, htmlEntities);
				if (specialCh != "not found")
				{
					//не использовать replace
					text.replace(index, htmlEntity.size() + 1, specialCh);
				}
			}
		};
		index++;
	}
	return text;
}