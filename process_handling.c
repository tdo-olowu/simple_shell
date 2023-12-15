#include "main.h"


/**
 * evaluate - execute a list of commands.
 * assumes that argv is in proper form.
 * @argv: a command followed by its arguments.
 * @envp: environment variables.
 * Return: returns -1 if command is exit, returns 1 else.
 */
int evaluate(char **argv, char **envp)
{
	int exe;

	/* 
	 * check if cmd  file exists before forking over
	 * pls wrap this fork n stuff inside a dummy process.
	 * let evaluate deal with the fork business and return either 1 or -1
	 * return -1 if cmd is exit. return 1 otherwise.
	 */
	exe = dummy_process(argv, envp);
	cid = fork();
	if (cid == -1)
	{
		perror("Couldn't fork program.");
		exit(EXIT_FAILURE);
	}
	else if (cid == 0)
	{
		printf("	child about to execute....\n"); /* DEBUG */
		exe = execve(argv[0], argv, envp);
		if (exe < 0)
		{
			perror("Couldn't execute command");
			printf("exe is %d\n", exe); /* DEBUG */
			/* exit(EXIT_FAILURE); */
			exit(EXIT_FAILURE);
		}
	}
	printf("	parent about to wait...\n"); /* DEBUG */
	wait(NULL);
	printf("evaluate function returning 1...\n"); /* DEBUG */

	return (exe);
}


/**
 * dummy_process - something to lock the child away
 * @argv: command, and its arguments.
 * @envp: environment variables
 * Return: always returns 1 for now.
 */
int dummy_process(char **argv, char **envp)
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
		exe = execve(argv[0], argv, envp);
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
