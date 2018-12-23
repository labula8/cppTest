
#include "endian.h"

void show_array_char(unsigned char array[], int array_size)
{
	for (int i = 0; i < array_size; i++)
	{
		printf("\n addr=0x %x ", (unsigned int)(&array[i]));
		printf("%d ", array[i]);
		printf("%c #", array[i]);
	}
	printf("\n array_size=%d \n", array_size);
}

int little_end(const unsigned int num)
{
	printf("%s, num=%d \n", __FUNCTION__, num);
	unsigned char szCh[8];
	unsigned char * pCh = NULL;
	pCh = (unsigned char*)&num;
	int size = sizeof(num);
	for (int i = 0; i < size; i++)
	{
		szCh[i] = *pCh;
		pCh++;
	}
	show_array_char(szCh, size);
	
	return 0;
}

int big_end(const int num)
{
	//
	return 0;
}