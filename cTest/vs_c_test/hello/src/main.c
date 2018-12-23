
#include <stdio.h>
#include <stdlib.h>

//linux
//#include <unistd.h>

#include "todo.h"
#include "hello.h"
#include "endian.h"
#include "gets.h"
#include "star.h"
#include "char.h"

void test()
{
	//fun_void();
	//test_baoliu();
	//test_hello();
	//todo();

	//unsigned int num = 0x01020304;
	//little_end(num);
	//test_gets();
	//test_star();
	test_char();
}

int main()
{
	printf("== hello! ==\n");
	test();

	printf("== exit! ==\n");

	//pause();
	system("pause"); //stdlib.h
	return EXIT_SUCCESS; //stdlib.h
	//return 0;
}