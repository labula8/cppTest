#define CREATE_DLL_API_DU _declspec(dllexport)

#include <iostream>
#include "DLL1.h"

using namespace std;

#if 0

void animal::getWide(int x)
{
	wide = x;
}

void CREATE_DLL_API_DU animal::getHeight(int y)
{
	high = y;
}

int CREATE_DLL_API_DU cat::outDate()
{
	return (wide + high); wide += wide; high += high;
}

int CREATE_DLL_API_DU dog::outDate()
{
	return (wide - high);
}

int CREATE_DLL_API_DU exportDate()
{
	return 666;
}

#endif
