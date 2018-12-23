
#include "gets.h"

/*
* 从控制台，读入，yes,no,来判断
*/
int test_gets()
{
	char buff[1024] = { 0 };
	gets(buff);
	printf("%s, you input buff=%s\n", __FUNCTION__, buff);

	if (0 == strcmp("yes", buff))
	{
		printf("ok yes!\n");
	}
	else if (0 == strcmp("no", buff))
	{
		printf("oh no!\n");
	}
	else
	{
		printf("ooohhh ?\n");
	}

	return 0;
}