#ifndef CCONSOLE_H_
#define CCONSOLE_H_

#include <atomic>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>

class CConsole
{
// public variables and functions
public:
	// class constructor
	CConsole();
	~CConsole();
	static CConsole* getInstance();
    void run(std::atomic<bool>& run);
protected:
	static CConsole* singleton;
};
#endif // CSTORAGE_H_