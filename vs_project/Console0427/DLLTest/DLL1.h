#pragma once

#ifdef CREATE_DLL_API_DU

#else
//������ʱ��ͷ�ļ����μӱ��룬����.cpp�ļ����ȶ��壬��ͷ�ļ�����������������ⲿʹ��ʱ��Ϊdllexport�������ڲ�����ʱ����Ϊdllimport
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
