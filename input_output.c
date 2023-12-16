#include "main.h"

/**
 * getcmd - used for reading user input or lines from file.
 * attempt at handling comments.
 * @buf: pointer to the input buffer
 * @lenptr: pointer to length of buffer
 * @filestr: filestream pointer.
 * Return: number of bytes read.
 */
ssize_t getcmd(char **buf, size_t *lenptr, FILE *filestr)
{
	int i;
	char prev_ch = '/', ch;
	ssize_t bytes_read;

	bytes_read = getline(buf, lenptr, filestr);
	/* try this: buffer[bytes_read - 1] = '\0' to remove newline */
	/* i also try to skip when char is comment. */
	if (bytes_read >= 0)
	{
		for (i = 0 ; (*buf)[i] != '\n' ; ++i)
		{
			ch = (*buf)[i];
			if ((!isalpha(prev_ch)) && (ch == '#'))
				break;
			prev_ch = ch;
		}
		(*buf)[i] = '\0';
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
 * use strtol
 * @n: integer as string
 * Return: -1 if n is not proper integer.
 */
long int convert_to_int(char *n)
{
	long int value, failure = -1, modulus = 256;
	const char *str = (const char *)n;
	char *endp;

	(void)modulus;
	value = strtol(str, &endp, 10);
	if (*endp != '\0')
		return (failure);

	return (value);
}
