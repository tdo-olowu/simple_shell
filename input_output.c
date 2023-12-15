#include "main.h"

/**
 * getcmd
 */
ssize_t getcmd(char **bufferptr, size_t *lenptr, FILE *filestr)
{
	int i;
	ssize_t bytes_read;

	bytes_read = getline(bufferptr, lenptr, filestr);
	if (bytes_read >= 0)
	{
		for (i = 0 ; (*bufferptr)[i] != '\n' ; ++i)
			;
		(*bufferptr)[i] = '\0';
		bytes_read -= 1;
	}

	return (bytes_read);
}
