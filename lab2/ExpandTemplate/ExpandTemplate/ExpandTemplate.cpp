#include <iostream>
#include "ExpandTemplate.h"
#include "ExpandTemplate.h"
#include <vector>
#include <map>
#include <optional>

namespace
{
	const int voidLink = -1;

	struct BohrVertex
	{
		std::map<char, int> next;
		std::optional<int> parent = std::nullopt;
		std::optional<int> suffixLink = std::nullopt;
		std::optional<int> suffixGoodLink = std::nullopt;
		std::map<char, int> autoMove;
		char symbol;
		bool leaf = false;
		std::string fullString;
	};

	using Bohr = std::vector<BohrVertex>;

	void AddStringInBohr(Bohr& bohr, std::string const& stringToAdd)
	{
		int currentVertexPos = 0;
		for (size_t i = 0; i < stringToAdd.length(); i++)
		{
			char symbol = stringToAdd[i];
			if (!bohr[currentVertexPos].next.contains(symbol))
			{
				BohrVertex newVertex;
				newVertex.parent = currentVertexPos;
				newVertex.symbol = symbol;
				bohr[currentVertexPos].next[symbol] = bohr.size();
				bohr.push_back(newVertex);
			}
			currentVertexPos = bohr[currentVertexPos].next[symbol];
		}
		bohr[currentVertexPos].fullString = stringToAdd;
		bohr[currentVertexPos].leaf = true;
	}

	int GetAutoMove(Bohr& bohr, int vertexPos, char symbol);

	int GetSuffixLink(Bohr& bohr, int vertexPos)
	{
		if (!bohr[vertexPos].suffixLink.has_value())
		{
			if (vertexPos == 0 || bohr[vertexPos].parent == 0)
			{
				bohr[vertexPos].suffixLink = 0;
			}
			else
			{
				bohr[vertexPos].suffixLink = GetAutoMove(bohr, GetSuffixLink(bohr, bohr[vertexPos].parent.value()), bohr[vertexPos].symbol);
			}
		}

		return bohr[vertexPos].suffixLink.value();
	}

	int GetSuffixGoodLink(Bohr& bohr, int vertexPos)
	{
		if (!bohr[vertexPos].suffixGoodLink.has_value()) {
			int vertexPosOnSuffixLink = GetSuffixLink(bohr, vertexPos);
			if (vertexPosOnSuffixLink == 0)
			{
				bohr[vertexPos].suffixGoodLink = 0;
			}
			else
			{
				bohr[vertexPos].suffixGoodLink = (bohr[vertexPosOnSuffixLink].leaf)
					? vertexPosOnSuffixLink
					: GetSuffixGoodLink(bohr, vertexPosOnSuffixLink);
			}
		}
		return bohr[vertexPos].suffixGoodLink.value();
	}

	int GetAutoMove(Bohr& bohr, int vertexPos, char symbol)
	{
		if (!bohr[vertexPos].autoMove.contains(symbol))
		{
			if (bohr[vertexPos].next.contains(symbol))
			{
				bohr[vertexPos].autoMove[symbol] = bohr[vertexPos].next[symbol];
			}
			else
			{
				bohr[vertexPos].autoMove[symbol] = vertexPos == 0
					? 0
					: GetAutoMove(bohr, GetSuffixLink(bohr, vertexPos), symbol);
			}
		}

		return bohr[vertexPos].autoMove[symbol];
	}

	bool CheckIfFound(Bohr& bohr, int vertexPos)
	{
		for (; vertexPos != 0; vertexPos = GetSuffixLink(bohr, vertexPos))
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

	void ReadUntilIsParam(Bohr& bohr, int& currentVertexPos, std::string const& tpl, int& stringIndex)
	{
		int newVertexPos = currentVertexPos;
		bool isParamEnded = false;

		while (!isParamEnded)
		{
			currentVertexPos = newVertexPos;
			stringIndex++;
			newVertexPos = GetAutoMove(bohr, newVertexPos, tpl[stringIndex]);
			bool isStringEnd = stringIndex >= tpl.length();
			bool isNewParamStarted = bohr[newVertexPos].parent != currentVertexPos;
			isParamEnded = !CheckIfFound(bohr, currentVertexPos) || isStringEnd || isNewParamStarted;
		}
		stringIndex--;
	}

	std::string GetStringToAdd(std::string const& tpl, TemplateParams const& params, std::string const& foundString, int lastCopiedPos, int currentPosition)
	{
		int uncopiedStringLength = currentPosition - lastCopiedPos - foundString.length() + 1; 
		std::string beforeFoundString = tpl.substr(lastCopiedPos, uncopiedStringLength);
		std::string stringToReplaceWith = params.find(foundString)->second;
		return beforeFoundString + stringToReplaceWith;
	}
}

std::string ExpandTemplate(std::string const& tpl, TemplateParams const& params)
{
	Bohr bohr = { BohrVertex() };
	std::string resultString;
	AddParamsInBohr(bohr, params);

	int vertexPos = 0;
	int lastCopiedPos = 0;
	for (int i = 0; i < tpl.length(); i++)
	{
		vertexPos = GetAutoMove(bohr, vertexPos, tpl[i]);

		if (CheckIfFound(bohr, vertexPos))
		{
			ReadUntilIsParam(bohr, vertexPos, tpl, i);
			resultString += GetStringToAdd(tpl, params, bohr[vertexPos].fullString, lastCopiedPos, i);
			vertexPos = 0;
			lastCopiedPos = i + 1;
		}
	}
	resultString += tpl.substr(lastCopiedPos);

	return resultString;
}
