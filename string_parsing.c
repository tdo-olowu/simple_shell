#include "main.h"


/**
 * make_tokens - tokenise a null-terminated string.
 * @str: the string to tokenise
 * @delim: the delimiter.
 * Return: array of strings i.e. the tokens.
 */
char **make_tokens(char *str, char *delim)
{
	int i;
	int buf = 64;
       	int bufsize = 64;
	char *temp, **tokens;

	tokens = malloc(buf * sizeof(char**));
	if (tokens == NULL)
		return (NULL);

	temp = strtok(str, delim);
	for (i = 0 ; temp != NULL ; ++i)
	{
		if (i >= bufsize)
		{
			bufsize += buf;
			tokens = realloc(tokens, bufsize * sizeof(char**));
			if (tokens == NULL)
			{
				perror("make_tokens: couldn't parse all input");
				free_table(tokens); /* why shouldn't we return partial output? */
				return (NULL);
			}
		}
		tokens[i] = strdup(temp);
		printf("token read: %s\n", tokens[i]); /* DEBUG LINE */
		temp = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	printf("..............TOKENS COMPLETE!...............\n"); /* DEBUG LINE */

	return (tokens);
}


/**
 * envcopy - summons and copies over the ENV variable somehow.
 * the issue is that I'm not allowed to use extern
 * then how tf am I supposed to access environ?!
 * Return: a copy of environ.
 */
char **envcopy(void)
{
	extern char **environ;
	int i = 0;
	int buf = 64, bufsize = 64;
	char **envp;

	envp = malloc(buf * sizeof(char**));
	if (envp == NULL)
		return (NULL);
	for (i = 0 ; environ[i] != NULL ; ++i)
	{
		envp[i] = strdup(environ[i]);
		if (envp[i] == NULL)
		{
			perror("Couldn't copy all env variables!");
			free_table(envp);
			return (NULL);
		}
	/*	printf("env copied!!! %s\n", envp[i]);  FOR DEBUG */
	}
	envp[i] = NULL;

	return (envp);
}



/**
 * cmd_as_dirs - process argv's first cmd so that executor can use it properly.
 * later, we'll add another argument - a list of paths to try?
 * this function is a primitive version of try-paths.
 * @argv: the list of commands.
 * Return: none
 */
void cmd_as_dirs(char **argv)
{
	char *dir_pre = "/bin/";
	int len1 = strlen(dir_pre);
	int len2 = strlen(argv[0]);
	int k;
	char *new_str = malloc((1 + len1 + len2) * sizeof(char));

	if (new_str != NULL)
	{
		for (k = 0 ; k < len1 ; ++k)
			new_str[k] = dir_pre[k];
		for (k = 0 ; k < len2 ; ++k)
			new_str[k + len1] = argv[0][k];
		new_str[k + len1] = '\0';
		argv[0] = strdup(new_str);
	}
}
