#include "Log.h"


void Log::error(const char *str)
{
	std::cout << "\nError : " << str << "\n" << std::endl;
}

void Log::info(const char *str)
{
	std::cout << "\nInfo : " << str << "\n" << std::endl;
}