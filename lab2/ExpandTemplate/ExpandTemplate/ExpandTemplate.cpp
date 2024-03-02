#include <iostream>
#include "ExpandTemplate.h"
#include "ExpandTemplate.h"
#include <vector>
#include <map>
#include <optional>

namespace
{
	// Посмотреть покрытие тестами
	struct BohrVertex
	{
		// Сравнить скорость с unordered
		std::map<char, size_t> next;
		// Избавиться от optional (Исправлено)
		// parentVertexIndex (Исправлено)
		size_t parentVertexIndex = std::string::npos;
		//SuffixLinkVertex (Исправлено)
		size_t suffixLinkVertex = std::string::npos;
		size_t suffixGoodLinkVertex = std::string::npos;
		// Хранить отдельно, чтобы не менять бор
		std::map<char, size_t> autoMove;
		char symbol;
		
		bool leaf = false;
		std::string fullString;
	};

	using Bohr = std::vector<BohrVertex>;

	void AddStringInBohr(Bohr& bohr, std::string const& stringToAdd)
	{
		size_t currentVertexPos = 0;
		for (auto it = stringToAdd.begin(); it != stringToAdd.end(); ++it)
		{
			char symbol = *it;
			if (!bohr[currentVertexPos].next.contains(symbol))
			{
				BohrVertex newVertex;
				newVertex.parentVertexIndex = currentVertexPos;
				newVertex.symbol = symbol;
				bohr[currentVertexPos].next[symbol] = bohr.size();
				bohr.push_back(newVertex);
			}
			currentVertexPos = bohr[currentVertexPos].next[symbol];
		}
		bohr[currentVertexPos].fullString = stringToAdd;
		bohr[currentVertexPos].leaf = true;
	}

	size_t GetAutoMove(Bohr& bohr, size_t vertexPos, char symbol);

	size_t GetSuffixLink(Bohr& bohr, size_t vertexPos)
	{
		if (bohr[vertexPos].suffixLinkVertex == std::string::npos)
		{
			if (vertexPos == 0 || bohr[vertexPos].parentVertexIndex == 0)
			{
				bohr[vertexPos].suffixLinkVertex = 0;
			}
			else
			{
				bohr[vertexPos].suffixLinkVertex = GetAutoMove(bohr, GetSuffixLink(bohr, bohr[vertexPos].parentVertexIndex), bohr[vertexPos].symbol);
			}
		}

		return bohr[vertexPos].suffixLinkVertex;
	}

	size_t GetSuffixGoodLink(Bohr& bohr, size_t vertexPos)
	{
		if (bohr[vertexPos].suffixGoodLinkVertex == std::string::npos) {
			size_t vertexPosOnSuffixLink = GetSuffixLink(bohr, vertexPos);
			if (vertexPosOnSuffixLink == 0)
			{
				bohr[vertexPos].suffixGoodLinkVertex = 0;
			}
			else
			{
				bohr[vertexPos].suffixGoodLinkVertex = (bohr[vertexPosOnSuffixLink].leaf)
					? vertexPosOnSuffixLink
					: GetSuffixGoodLink(bohr, vertexPosOnSuffixLink);
			}
		}

		return bohr[vertexPos].suffixGoodLinkVertex;
	}

	size_t GetAutoMove(Bohr& bohr, size_t vertexPos, char symbol)
	{
		// Сохранить ссылку на элемент, а не искать 
		if (!bohr[vertexPos].autoMove.contains(symbol))
		{
			if (bohr[vertexPos].next.contains(symbol))
			{
				bohr[vertexPos].autoMove[symbol] = bohr[vertexPos].next[symbol];
			}
			else
			{
				bohr[vertexPos].autoMove[symbol] = (vertexPos == 0)
					? 0
					: GetAutoMove(bohr, GetSuffixLink(bohr, vertexPos), symbol);
			}
		}

		return bohr[vertexPos].autoMove[symbol];
	}

	bool CheckIfFound(Bohr& bohr, size_t vertexPos)
	{
		for (; vertexPos != 0; vertexPos = GetSuffixGoodLink(bohr, vertexPos))
		{
			if (bohr[vertexPos].leaf)
			{
				return true;
			}
		}

		return false;
	}

	void AddParamsInBohr(Bohr& bohr, TemplateParams const& params)
	{
		for (auto& param : params)
		{
			AddStringInBohr(bohr, param.first);
		}
	}

	// Переименовать
	size_t ReadUntilIsParam(Bohr& bohr, size_t currentVertexPos, std::string const& tpl, std::string::const_iterator& it)
	{
		size_t newVertexPos = currentVertexPos;
		bool isParamEnded = it + 1 == tpl.cend();

		if (isParamEnded)
		{
			return currentVertexPos;
		}

		while (!isParamEnded)
		{
			currentVertexPos = newVertexPos;
			newVertexPos = GetAutoMove(bohr, newVertexPos, *(++it));
			bool isStringEnd = it + 1 == tpl.cend();
			bool isNewParamStarted = bohr[newVertexPos].parentVertexIndex != currentVertexPos;
			isParamEnded = !CheckIfFound(bohr, currentVertexPos) || isStringEnd || isNewParamStarted;
		}
		it--;

		return currentVertexPos;
	}

	std::string GetStringToAdd(TemplateParams const& params, std::string const& foundString, 
		std::string::const_iterator lastCopiedPos, std::string::const_iterator currentPosition)
	{
		size_t uncopiedStringLength = currentPosition - lastCopiedPos - foundString.length() + 1; 
		std::string beforeFoundString = std::string(lastCopiedPos, lastCopiedPos + uncopiedStringLength);
		std::string stringToReplaceWith = params.find(foundString)->second;
		return beforeFoundString + stringToReplaceWith;
	}
}

std::string ExpandTemplate(std::string const& tpl, TemplateParams const& params)
{
	Bohr bohr = { BohrVertex() };
	std::string resultString;
	AddParamsInBohr(bohr, params);

	size_t vertexPos = 0;
	auto lastCopiedPos = tpl.begin();
	for (auto it = tpl.begin(); it != tpl.end(); ++it)
	{
		vertexPos = GetAutoMove(bohr, vertexPos, *it);

		if (CheckIfFound(bohr, vertexPos))
		{
			vertexPos = ReadUntilIsParam(bohr, vertexPos, tpl, it);
			resultString += GetStringToAdd(params, bohr[vertexPos].fullString, lastCopiedPos, it);
			vertexPos = 0;
			lastCopiedPos = it + 1;
		}
	}
	resultString += std::string(lastCopiedPos, tpl.end());

	return resultString;
}
