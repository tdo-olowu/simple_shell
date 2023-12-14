#include "main.h"

/**
 * getcmd - reads the input from stdin.
 * @buffer: address of buffer to read to
 * @len: address of buffer length.
 * @stream: pointer of file stream.
 * Return: number of bytes read.
 */
ssize_t getcmd(char **buffer, size_t *len, FILE *stream)
{
	ssize_t bytes_read;

	bytes_read = getline(buffer, len, stream);
	return (bytes_read);
}


/**
 * genv - get the value of an environment variable.
 * @name: the key whose value is sought.
 * Return: value of the env key.
 */
char *genv(char *name)
{
	extern char **environ;
	int i;
	char *n; char *v;

	for (i = 0 ; environ[i] != NULL ; ++i)
	{
		n = strtok(environ[i], "=");
		if (strcmp(name, n) == 0)
		{
			v = strtok(environ[i], "=");
			return (v);
		}
	}

	return (NULL);
}
