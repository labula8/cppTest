#pragma once

#ifdef CREATE_DLL_API_DU

#else
//当编译时，头文件不参加编译，所以.cpp文件中先定义，后头文件被包含进来，因此外部使用时，为dllexport，而在内部编译时，则为dllimport
#define CREATE_DLL_API _declspec(dllimport)
#endif

#if 0

class CREATE_DLL_API_DU animal
{
public:
	virtual int outDate() = 0;
	void getWide(int x);
	void getHeight(int y);

protected:
	int wide;
	int high;

};

class CREATE_DLL_API_DU cat : public animal {
public:
	int outDate();
};

class CREATE_DLL_API_DU dog : public animal
{
public:
	int outDate();
};

int CREATE_DLL_API_DU exportDate();

#endif
