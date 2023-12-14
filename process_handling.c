#include "main.h"

/**
 * evaluate - evaluates a command.
 * @argv: list of arguments
 * @envp: environment for execve
 * Return: status
 */
int evaluate(char **argv, char **envp)
{
	int exe;
	char *cmd = argv[0];
	char *pathvs;
	int (*func)(void *) = search_bins(cmd);
	path_list *dirs;

	if (func == NULL)
	{
		pathvs = getenv("PATH");
		dirs = build_path_chain(tokenify(pathvs, ":"));
		if (dirs == NULL)
		{
			perror("Could not resolve paths");
			return (-1);
		}
		while (dirs != NULL)
		{
			argv[0] = joinstr(dirs->dir, cmd);
			exe = attempt(argv, envp);
			if (exe < 0)
				dirs = dirs->next;
			else
			{
				cleanup(NULL, NULL, dirs);
				return (1);
			}
		}
	}

	return (func(NULL));
}


/**
 * attempt - attempt to execute a non-builtin
 * @argv: list of arguments for execve
 * @envp: environment for execve
 * Return: -1 for failure, 1 for success.
 */
int attempt(char **argv, char **envp)
{
	pid_t cid;

	cid = fork();
	if (cid == 0)
	{
		if (execve(argv[0], argv, envp) < 0)
			return (-1);
	}
	wait(NULL);

	return (1);
}


/**
 * search_bins - function to return functions
 * @cmd: the key to decide which function to return.
 * Return: pointer to a function.
 */
int (*search_bins(char *cmd))(void*)
{
	int i;
	bin_t builtins[] = {{"exit", leave},
			  {"env", _env},
			  {NULL, NULL}};

	for (i = 0 ; builtins[i].name != NULL ; ++i)
	{
		if (strcmp(cmd, builtins[i].name) == 0)
			return (builtins[i].f);
	}

	return (NULL);
}
