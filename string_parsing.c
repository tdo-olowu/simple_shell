#include "main.h"


/**
 * make_tokens - tokenise a null-terminated string.
 * @str: the string to tokenise
 * @delim: the delimiter.
 * Return: array of strings i.e. the tokens.
 */
char **make_tokens(char *str, char *delim)
{
	int i, buf = 64, bufsize = 64;
	char *temp, **tokens;

	printf("about to make tokens str is %s\n", str);
	if (str == NULL)
		return (NULL);
	tokens = malloc(buf * sizeof(char **));
	if (tokens == NULL)
		return (NULL);

	temp = strtok(str, delim);
	for (i = 0 ; temp != NULL ; ++i)
	{
		if (i >= bufsize)
		{
			bufsize += buf;
			tokens = realloc(tokens, bufsize * sizeof(char **));
			if (tokens == NULL)
			{
				free_table(tokens);
				return (NULL);
			}
		}
		tokens[i] = strdup(temp);
		if (tokens[i] == NULL)
		{
			perror("couldn't parse all input.");
			free_table(tokens);
			return (NULL);
		}
		temp = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	printf("About to leave tokens. printing tokens...\n");
	pargv(tokens);

	return (tokens);
}



/**
 * envcopy - summons and copies over the ENV variable somehow.
 * this copy of envcopy is destructive. pls modify.
 * @environ: the environment variable.
 * Return: a copy of environ.
 */
char **envcopy(char **environ)
{
	int i = 0;
	int buf = 64;
	char **envp;

	envp = malloc(buf * sizeof(char **));
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
	}
	envp[i] = NULL;

	return (envp);
}



/**
 * genv - an implementation of getenv.
 * @name: the name of the value
 * @environ: the environment.
 * Return: the value of the name
 * pls fix leading whitespace.
 */
char *genv(char *name, char **environ)
{
	int i;
	char *n, *v, *temp;
	char **env = envcopy(environ);

	printf("in genv name is : %s\n", name);
	if (env != NULL)
	{
		v = NULL;
		printf("envcopy successful\n");
		puts("\n\n");
		for (i = 0 ; env[i] != NULL ; ++i)
		{
			temp = strdup(env[i]);
			if (temp == NULL)
				return (NULL);
			printf("temp: %s\n", temp);
			n = strtok(temp, "=");
			printf("name: %s\n", n);
			printf("diff btw name and n is %d\n", strcmp(name, n));
			if (strcmp(name, n) == 0)
			{
				v = strtok(NULL, "=");
				printf("value: %s duplicating tempn", v);
				temp = strdup(v);
				if (temp == NULL)
				{
					free(env);
					return (NULL);
				}
				printf("temp successfully copied: %s\n", temp);
				free(env);
				return (temp);
			}
			free(temp);
		}
		free(env);
		printf("in genv, v has no match\n");
		return (NULL);
	}

	printf("in genv, couldn't resolve envp\n");
	return (NULL);
}


/**
 * cmd_as_dir - process argv's first cmd so that executor can use it properly.
 * later, we'll add another argument - a list of paths to try?
 * this function is a primitive version of try-paths.
 * @str: the suffix.
 * @prefix: what to append to the str e.g. /bin/
 * Return: pointer to char
 */
char *cmd_as_dir(char *str, char *prefix)
{
	char *old_cmd = str;
	char *new_str;
	int len1, len2;
	int k;

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

			return (new_str);
		}
		perror("Couldn't prepend directory");
		return (NULL);
	}

	return (old_cmd);
}
