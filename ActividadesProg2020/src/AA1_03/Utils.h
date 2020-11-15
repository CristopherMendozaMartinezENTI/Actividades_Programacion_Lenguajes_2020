#include <iomanip>
#include <sstream>
#include <string>

std::string FloatToString(float num, int precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << num;
	std::string number = stream.str();
	return number;
}