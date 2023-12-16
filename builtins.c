#include "main.h"


/**
 * exec_bin - execute builtins, return status
 * @argv: the list of arguments.
 * @envp: environment variables just in case.
 * Return: 1 for success, -1 for failure.
 */
int (*exec_bin(char **argv, char **envp))(char **)
{
	size_t i;
	size_t range;
	int (*function)(char **);
	char *bin_name;
	bin_type bin_map[] = {{"exit", hsh_exit},
			      {"env", penv}};

	/* envp isn't useful for now */
	(void)envp;
	range = sizeof(bin_map) / sizeof(bin_type);
	for (i = 0 ; i < range ; ++i)
	{
		bin_name = (bin_map[i]).name;
		function = (bin_map[i]).func;
		if (strcmp(argv[0], bin_name) == 0)
		{
			return (function);
		}
	}

	return (NULL);
}


/**
 * hsh_exit - exits the hshell.
 * @argv: what do you need this for?
 * Return: value to break control of loop.
 */
int hsh_exit(char **argv)
{
	(void)argv;
	return (-1);
}


/**
 * penv - prints environment variables.
 * @envp: list of environment variables.
 * Return: always returns 1. sho
 */
int penv(char **envp)
{
	int i;
	char **env = envcopy(envp);

	if (env != NULL)
	{
		for (i = 0 ; env[i] != NULL ; ++i)
		{
			printf("%s\n", env[i]);
		}
	}
	else
		perror("Couldn't print environment variables");

	return (1);
}
