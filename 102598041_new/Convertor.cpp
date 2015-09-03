#include "Convertor.h"


Convertor::Convertor(void)
{
}


Convertor::~Convertor(void)
{
}

int Convertor::ConvertStringToInteger(std::string str)
{
	int valueOfInt;
	std::stringstream convtToInt(str);
	convtToInt >> valueOfInt;
	return valueOfInt;
}