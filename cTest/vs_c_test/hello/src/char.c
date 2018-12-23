
#include "char.h"

void test_char()
{
	for (int i = 0; i < 256; i++)
	{
		unsigned char ch = i;
		printf("ch=0x %x %d %c \n", ch, ch, (char)ch);
	}
}