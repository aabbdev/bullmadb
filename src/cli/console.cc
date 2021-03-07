#include "console.h"
CConsole *CConsole::singleton = 0;
CConsole::CConsole(){
    singleton = this;
}
CConsole::~CConsole(){
    singleton = nullptr;
}
CConsole *CConsole::getInstance()
{
	return singleton;
}
void CConsole::run(std::atomic<bool>& run){
    std::string buffer;

    while (run.load())
    {
        std::cin >> buffer;
        if (buffer == "Quit")
        {
            run.store(false);
        }
    }
}