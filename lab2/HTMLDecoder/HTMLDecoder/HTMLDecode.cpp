#include <string>
#include <iostream>
#include "HTMLDecode.h"
#include <map>

//���������� � ���� �����
//���������� �� ����������� ������ ������ � map
//�������� ���� �� ����� find
std::string getSpecialChDef(std::string htmlEntity, std::map<std::string, std::string> htmlEntities)
{
	for (auto& item: htmlEntities)
	{
		if (item.first == htmlEntity)
		{
			return item.second;
		}
	}
	//������ ������ ��������� not found
	return "not found";
}

std::string HtmlDecode(std::string const& html)
{
	std::map<std::string, std::string> htmlEntities = 
	{
		{"&quot", "\""},
		{"&apos", "�"},
		{"&lt", "<"},
		{"&gt", ">"},
		{"&amp", "&"}
	};
	std::string text = html;
	std::string specialCh = "";
	bool isTextContainsHtmlEntities = true;
	//int ���� ���� size_t
	int index = 0;
	//��� �������
	//textContainsHtmlEntities
	while (isTextContainsHtmlEntities)
	{
		index = text.find("&", index);
		isTextContainsHtmlEntities = index != -1;
		if (isTextContainsHtmlEntities)
		{
			int i = index;
			std::string htmlEntity = "";
			//������������ string_view
			//�� ������� ��������� ����� ������
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
					//�� ������������ replace
					text.replace(index, htmlEntity.size() + 1, specialCh);
				}
			}
		};
		index++;
	}
	return text;
}