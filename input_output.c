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
	char *n, *v, *temp;

	for (i = 0 ; environ[i] != NULL ; ++i)
	{
		temp = malloc(sizeof(environ[i]));
		if (temp == NULL)
			continue;
		n = strtok(temp, "=");
		if (strcmp(name, n) == 0)
		{
			v = strtok(temp, "=");
			return (v);
		}
	}

	return (NULL);
}
