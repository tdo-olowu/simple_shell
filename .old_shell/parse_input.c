#include "main.h"

/**
 * tokenify - (verb) change a sentence into tokens.
 * @str: the string to tokenify.
 * Return: pointer to first string.
 */
char **tokenify(char *str, char *delim)
{
	size_t bufsize, i = 0, BUF = 64;
	char *word = strtok(str, delim);
	char **tokens = malloc(BUF * sizeof(char*));

	if (tokens == NULL)
		return (NULL);

	for (i = 0, bufsize = BUF ; word != NULL ; ++i)
	{
		if (i == bufsize)
		{
			bufsize += BUF;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (tokens == NULL)
			{
				perror("Can't read anymore");
				break;
			}
		}
		tokens[i] = strdup(word);
		word = strtok(str, delim);
	}
	tokens[i] = NULL;

	return (tokens);
}


/**
 * joinstr - turn a command into a path.
 * @cmd: command
 * @pre: prefix.
 * Return: the concatenation of both.
 */
char *joinstr(char *pre, char *cmd)
{
	int i = strlen(pre);
	int j = strlen(cmd);
	int k;
	char *path = malloc((1 + i + j) * sizeof(char));
	if (path == NULL)
		return (NULL);

	for (k = 0 ; k < i ; ++k)
		path[k] = pre[k];
	for ( ; k < i + j ; ++k)
		path[k] = cmd[k - i];

	return (path);
}
