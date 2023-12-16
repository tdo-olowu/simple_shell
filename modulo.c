#include <stdio.h>


int main(void)
{
	int i = -300;

	for (i = -300 ; i < 301 ; ++i)
	{
		printf("%d  ", i % 256);
	}
	putchar('\n');

	return (0);
}
