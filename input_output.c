#include "main.h"

/**
 * getcmd - used for reading user input or lines from file.
 * @bufferptr: pointer to the input buffer
 * @lenptr: pointer to length of buffer
 * @filestr: filestream pointer.
 * Return: number of bytes read.
 */
ssize_t getcmd(char **bufferptr, size_t *lenptr, FILE *filestr)
{
	int i;
	ssize_t bytes_read;

	bytes_read = getline(bufferptr, lenptr, filestr);
	/* try this: buffer[bytes_read - 1] = '\0' to remove newline */
	if (bytes_read >= 0)
	{
		for (i = 0 ; (*bufferptr)[i] != '\n' ; ++i)
			;
		(*bufferptr)[i] = '\0';
		bytes_read -= 1;
	}

	return (bytes_read);
}
