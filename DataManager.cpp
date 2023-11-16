#include "Headers/DataManager.h"
using namespace std;
#include <string>

void DataManager::GetNames() 
{
    const char* path = "Assets/Data/Names.txt";

    string myText;
    ifstream MyReadFile(path);

    while (getline(MyReadFile, myText)) {
        string tmp = myText;
        Names.push_back(tmp);
    }

    // Close the file
    MyReadFile.close();
}

void DataManager::GetIntroStory()
{
    const char* path = "Assets/Data/IntroStory.txt";

    string myText;
    ifstream MyReadFile(path);

    while (getline(MyReadFile, myText)) {
        IntroLines.push_back(myText);
    }

    // Close the file
    MyReadFile.close();
}

void DataManager::GetPhasesStory()
{
    const char* path = "Assets/Data/Phases.txt";

    string myText;
    ifstream MyReadFile(path);

    while (getline(MyReadFile, myText)) {
        PhasesLines.push_back(myText);
    }

    // Close the file
    MyReadFile.close();
}
