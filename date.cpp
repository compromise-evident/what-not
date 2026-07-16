//Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
int main()
{	
	
	
	std::string date;
	
	//Gets date & time.
	{	auto now = std::chrono::system_clock::now();
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
		std::tm localTime; localtime_r(&currentTime, &localTime);
		std::ostringstream oss; oss << std::put_time(&localTime, "%Y_%m_%d_%H:%M:%S"); date = oss.str();
	}
	
	std::cout << date; //Prints 2026_07_31_20:34:55
}
