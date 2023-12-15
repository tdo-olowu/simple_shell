#include "main.h"


/**
 * evaluate - execute a list of commands.
 * assumes that argv[0] is in dir form.
 * @argv: a command followed by its arguments.
 * @envp: environment variables.
 * Return: returns -1 if command is exit, returns 1 else.
 */
int evaluate(char **argv, char **envp)
{
	int status;
	int (*exe)(void);

	exe = exec_bin(argv, envp);
	if (exe == NULL)
	{
	/* 
	 * check if cmd  file exists before forking over
	 * pls wrap this fork n stuff inside a dummy process.
	 * let evaluate deal with the fork business and return either 1 or -1
	 * return -1 if cmd is exit. return 1 otherwise.
	 */
		/* prep argv[0] and try every path */
		status = dummy_process(cmd, argv, envp);
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
