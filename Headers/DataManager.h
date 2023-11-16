#include <iostream>
#include <fstream>
#include <vector>

class DataManager
{
public:
	void GetNames();
	void GetIntroStory();

	std::vector<std::string> Names;
	std::vector<std::string> IntroLines;
};