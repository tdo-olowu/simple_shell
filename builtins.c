#include "main.h"


/**
 * exec_bin - execute builtins, return status
 * @argv: the list of arguments.
 * @envp: environment variables just in case.
 * Return: 1 for success, -1 for failure.
 */
int (*exec_bin(char **argv, char **envp))(char **, char **)
{
	size_t i;
	size_t range;
	int (*function)(char **, char **);
	char *bin_name;
	bin_type bin_map[] = {{"env", penv},
			      {"cd", hsh_cd}};

	if (argv == NULL)
		return (NULL);
	if (*argv == NULL)
	{
		return (NULL);
	}
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
 * penv - prints environment variables.
 * @argv: list
 * @envp: list of environment variables.
 * Return: always returns 1. sho
 */
int penv(char **argv, char **envp)
{
	int i;
	char **env = envp;

	(void)argv;
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


/**
 * hsh_cd - changes the current directory.
 * @argv: list of arguments.
 * @envp: lsdi
 * Return: always returns 1.
 */
int hsh_cd(char **argv, char **envp)
{
	const char *new_dir;
	int dir_change = -1;
	int env_change;
	size_t ac = count_args(argv);
	struct stat filetest;

	(void)envp;
	if (ac == 1)
	{
		new_dir = getenv("HOME");
		if (new_dir == NULL)
		{
			perror("hsh");
			return (1);
		}
		dir_change = chdir(new_dir);
	}
	else if (ac == 2)
	{
		new_dir = (const char *)argv[1];
		if ((stat(new_dir, &filetest) == 0) && S_ISDIR(filetest.st_mode))
			dir_change = chdir(new_dir);
		else
			return (1);
	}
	else
	{
		perror("hsh");
		return (1);
	}
	/* this might cause issues. perror for ac > 2 will success? */
	if (dir_change < 0)
	{
		perror("hsh");
	}
	env_change = setenv("PWD", new_dir, 1);
	if (env_change < 0)
		perror("hsh");

	return (1);
}


/**
 * is_exit - checks if cmd is of form 'exit n'
 * if you're getting narrowing conv, its ret exitstat
 * @argv: list of commands.
 * Return: -1 if invalid exit command. exit stat else.
 */
int is_exit(char **argv)
{
	int failure = -1, success = 0;
	long int exit_stat;
	int good_bad = -10;
	size_t ac;
	const char *ex = "exit";
	char *msg = "Usage: exit n ; 0 <= n <= 255";

	ac = count_args(argv);
	if ((ac < 1) || (ac > 2))
	{
		if ((ac > 2) && (strcmp((const char *)argv[0], ex) == 0))
			perror(msg);
		if ((ac != 0) && (strcmp((const char *)argv[0], ex) == 0))
			return (good_bad);
		return (failure);
	}
	if (ac == 1)
	{
		if (strcmp((const char *)argv[0], ex) == 0)
			return (success);
		return (failure);
	}
	if (ac == 2)
	{
		if (strcmp((const char *)argv[0], ex) == 0)
		{
			exit_stat = convert_to_int(argv[1]);
			if (exit_stat < 0)
			{
				perror(msg);
				return (good_bad);
			}
			return ((int)exit_stat);
		}
		return (failure);
	}

	return (failure);
}
