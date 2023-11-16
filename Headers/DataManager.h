#include <iostream>
#include <fstream>
#include <vector>

class DataManager
{
public:
	void GetNames();
	void GetIntroStory();
	void GetPhasesStory();

	std::vector<std::string> Names;
	std::vector<std::string> IntroLines;
	std::vector<std::string> PhasesLines;
};