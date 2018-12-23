
#include "star.h"

/*
star print

  *
   **
*   ***
**   ****
**************
**   ****
*   ***
   **
  *
*/
void test_star()
{
	//�ɻ��ϰ���-0-4
	for (int i = 0; i < 4; i++)
	{
		left_star_up(i);
		right_star_up(i);
		printf("\n");
	}

	//�ɻ�����-5
	for (int i = 0; i < 16; i++)
	{
		printf("*");
	}
	printf("\n");

	//�ɻ��°���-6-9
	for (int i = 5; i < 9; i++)
	{
		left_star_down(i-5);
		right_star_down(i-5);
		printf("\n");
	}
}

void left_star_up(const int line)
{
	if (line < 2)
	{
		printf("   ");
	}
	else
	{
		for (int i = 0; i < line - 1; i++)
		{
			printf("*");
		}

		printf("   ");
	}
}

void right_star_up(const int line)
{
	for (int i = 0; i < line+1; i++)
	{
		printf("*");
	}
}

void left_star_down(const int line)
{
	if (line < 2)
	{
		for (int i = 2 - line; i > 0; i--)
		{
			printf("*");
		}

		printf("   ");
	}
	else
	{
		printf("   ");
	}
}

void right_star_down(const int line)
{
	for (int i = 4 - line; i > 0; i--)
	{
		printf("*");
	}
}