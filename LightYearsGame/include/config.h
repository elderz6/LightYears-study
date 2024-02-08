#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "C:/Users/elder/Desktop/GameCpp/LightYears/LightYearsGame/assets/";
#endif
}
