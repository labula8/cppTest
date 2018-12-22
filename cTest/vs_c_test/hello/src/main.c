
#include <stdio.h>

//system("xxx")
#include <stdlib.h>

//linux
//#include <unistd.h>

#include "todo.h"

void test()
{
	todo();
}

int main()
{
	printf("hello!");
	test();

	//pause();
	system("pause");

	return 0;
}