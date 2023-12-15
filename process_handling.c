#include "main.h"


/**
 * evaluate - execute a list of commands.
 * @argv: a command followed by its arguments.
 * @envp: environment variables.
 * Return: returns -1 if command is exit, returns 1 else.
 */
int evaluate(char **argv, char **envp)
{
	int status;
	int (*exe)(void);
	char *path, *pvalue, *msg, *cmd = argv[0];
	char **paths;
	dir_type dir_node;

	exe = exec_bin(argv, envp);
	msg = "Couldn't resolve PATH";
	if (exe == NULL)
	{
		pvalue = genv("PATH");

		if (pvalue == NULL)
			return (panic(msg, NULL, NULL, 1));
		paths = make_tokens(pvalue);
		if (paths == NULL)
			return (panic(msg, pvalue, NULL, 1));
		dir_node = build_dir_chain(paths);
		if (dir_node == NULL)
			return (panic(msg, pvalue, paths, 1));

		while (dir_node != NULL)
		{
			path = cmd_as_dir(cmd, dir_node->dir);
			if (path == NULL)
			{
				free(path);
				return (panic(msg, pvalue, paths, 1))
			}
			/* does the file exist? */
			/* try just one file. our job is not to try every */
			if (stat(path))
			{
				printf("Filefound: %s\n", path); /* DEBUG */
				status = dummy_process(path, argv, envp);
				break;
			}
			dir_node = dir_node->next;
		}
		cleanup(pvalue, paths);
	}
	else
		status = exe();

	return (status);
}


/**
 * dummy_process - something to lock the child away
 * @cmd: the command as a path
 * @argv: command, and its arguments.
 * @envp: environment variables
 * Return: always returns 1 for now.
 */
int dummy_process(char *cmd, char **argv, char **envp)
{
	int exe;
	pid_t cid;

	cid = fork();
	if (cid == -1)
	{
		perror("Couldn't create subprocess");
		exit(EXIT_FAILURE);
	}
	else if (cid == 0)
	{
		exe = execve(cmd, argv, envp);
		if (exe < 0)
		{
			perror("Couldn't execute command");
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);

	return (1);
}

/**
 * if (WIFEXITED(exe) && WEXITSTATUS(exe) == EXIT_SUCCESS)
 * 	child succeeded.
 * else
 * 	child failed to execute.
 */
