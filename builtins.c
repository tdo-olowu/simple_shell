#include "main.h"


/**
 * exec_bin - execute builtins, return status
 * @argv: the list of arguments.
 * @envp: environment variables just in case.
 * Return: 1 for success, -1 for failure.
 */
int exec_bin(char **argv, char **envp)
{
	/**
	 * here's the plan - extract argv[0]
	 * compare it against a list of bins.
	 * where there's a match, 'execute' and return value
	 * if no match, return -1
	 * notice that the bins are essentially "void" functions
	 */
	int i;
	int status = -1; /* assume it does not exist */
	int (*function)(void); /* ptr to funct that takes void* and give int */
	char *arg = argv[0];
	char *bin_name;
	bin_type bin_map[] = {{"exit", hsh_exit},
			      {"env", penv},
			      {NULL, NULL}};

	for (i = 0 ; i < sizeof(bin_map) ; ++i)
	{
		bin_name = (bin_map[i])->name;
		if (bin_name == NULL)
			return (-1); /* depends on order of NULL */
		function = &(bin_map[i])->func;
		if (strcmp(arg, bin_name) == 0)
		{
			status = function(); /* should get an integer */
			return (status);
		}
	}

	return (status);
}


/**
 * hsh_exit - exits the hshell.
 * Return: value to break control of loop.
 */
int hsh_exit(void)
{
	return (-1);
}


/**
 * penv - prints environment variables.
 * Return: always returns 1. sho
 */
int penv(void)
{
	int i;
	char **env = envcopy();

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
