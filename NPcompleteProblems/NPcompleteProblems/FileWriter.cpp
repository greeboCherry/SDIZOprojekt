#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include <ctime>
#include <chrono>
class FileWriter
{
public:
	static void saveToFile(std::string fileName, std::string textContent)
	{
		fileName = "output/" + fileName + ".txt";

		std::time_t currentTime = std::time(NULL);
		//		std::string timeString(std::asctime(std::localtime(&currentTime)));


		textContent = textContent;//+ timeString;
		std::ofstream outfile(fileName, std::ofstream::out | std::ofstream::app);	//app starts writing at the end of file, out overwrites it
		if (outfile.is_open())
		{
			outfile.write(textContent.c_str(), textContent.size());
			outfile.close();
		}
		else
			std::cout << "Couldn't create file. Make sure that there is <output> folder in exe location.\nYour results\n" << textContent << std::endl;
	}
};