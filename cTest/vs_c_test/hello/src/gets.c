
#include "gets.h"

/*
* �ӿ���̨�����룬yes,no,���ж�
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