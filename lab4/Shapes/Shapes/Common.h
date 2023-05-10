#pragma once
#include <string>
#include "CPoint.h"

const int COLOR_LEN = 6;
const int COLOR_RADIX = 16;
const double PI = 3.1415;

bool IsEquals(double leftValue, double rightValue);

bool StringToUint32(std::string const& str, uint32_t& uint32);

std::string GetHexStrFromUint32(uint32_t const& uint32, int len);

double GetLineLength(CPoint start, CPoint end);
