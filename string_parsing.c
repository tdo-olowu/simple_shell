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
				/* why can't we return partial tokens */
				free_table(tokens);
				return (NULL);
			}
		}
		/* this line may cause memory leaks */
		tokens[i] = strdup(temp);
		if (tokens[i] == NULL)
		{
			perror("couldn't parse all input.");
			free_table(tokens);
			return (NULL);
		}
		/* printf("token read: %s\n", tokens[i]); DEBUG LINE */
		temp = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	/* printf("..............TOKENS COMPLETE!...............\n"); DEBUG LINE */

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
	int buf = 64;
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
 * genv - an implementation of getenv.
 * @name: the name of the value
 * @env: the environment variable.
 * Return: the value of the name
 * pls fix leading whitespace.
 */
char *genv(char *name, char **env)
{
	int i;
	char *n; char *v;

	printf("	inside genv.\n");
	for (i = 0 ; env[i] != NULL ; ++i)
	{
		n = strtok(env[i], "=");
		if (strcmp(name, n) == 0)
		{
			v = strtok(NULL, "=");
			return (v);
		}
	}

	return (NULL);
}


/**
 * cmd_as_dir - process argv's first cmd so that executor can use it properly.
 * later, we'll add another argument - a list of paths to try?
 * this function is a primitive version of try-paths.
 * @str: the suffix.
 * @pref: what to append to the str e.g. /bin/
 * Return: pointer to char
 */
char *cmd_as_dir(char *str, char *prefix)
{
	char *old_cmd = str;
	char *new_str;
	int len1, len2;
	int k;

	printf("	changing arg to dir.\n");
	if (prefix != NULL)
	{
		len1 = strlen(prefix);
		len2 = strlen(old_cmd);
		/* 2 cuz of that pesky / not included in PATh */
		new_str = malloc((2 + len1 + len2) * sizeof(char));

		if (new_str != NULL)
		{
			for (k = 0 ; k < len1 ; ++k)
				new_str[k] = prefix[k];
			new_str[k] = '/';
			for (k = 0 ; k < len2 ; ++k)
				new_str[k + 1 + len1] = old_cmd[k];
			new_str[k + 1 + len1] = '\0';
			printf("new str - %s\n", new_str); /* DEBUG */

			return (new_str);
		}
		perror("Couldn't prepend directory");
		return (NULL);
	}

	return (old_cmd);
}
