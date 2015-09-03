#pragma once
#include <iostream>

using namespace std;

class ObserverTextUIInterface
{
public:
	ObserverTextUIInterface(void);
	~ObserverTextUIInterface(void);
	virtual void UpdateComponents(int, string, string) = 0;
	virtual void UpdateConnection(int, int, string) = 0;
};

