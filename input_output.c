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


/**
 * count_args - count the number of arguments in an argv.
 * @argv: list of string.
 * Return: number of arguments.
 */
size_t count_args(char **argv)
{
	int i;
	size_t count = 0;

	if (argv == NULL)
		count = 0;
	else
	{
		for (i = 0, count = 0 ; argv[i] != NULL ; ++i)
			++count;
	}

	return (count);
}


/**
 * convert_to_int - convert a string to integer
 * this is specifically for is_exit to use.
 * @n: integer as string
 * Return: -1 if n is not proper integer.
 */
int convert_to_int(char *n)
{
	int value, modulus = 256;
	const char *str = (const char *)n;

	value = itoa(str);
	/* this is if input is actually valid integer */
	value = abs(value % modulus);
	/* should input be improper, return -1 */

	return (value);
}
