#include "main.h"


/**
 * evaluate - return 1 for success, -1 for failure.
 * assumes that argv is in proper form.
 */
int evaluate(char **argv, char **envp)
{
	int exe;
	pid_t cid;

	/* check if cmd exists before forking over */
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
	printf("	parent about to wait...\n");
	wait(NULL);
	printf("evaluate function returning 1...\n");

	return (1);

	/* actually, I want to return -1 only if the command is exit.
	if (WIFEXITED(exe) && WEXITSTATUS(exe) == 0)
	{
		printf("child process executed successfully.\n");
		return (1);
	}
	else
	{
		printf("Child process failed to execute");
		return (-1);
	}
	*/
}


/**
 * dummy_process - something to lock the child away
 */
int dummy_process(char **argv, char **envp)
{
	int exe;
	int cid = fork();

	if (cid == 0)
	{
		printf("	child.:\n");
		exe = execve(argv[0], argv, envp);
		if (exe < 0)
		{
			perror("hsh: couldn't execute command");
			exit(EXIT_FAILURE);
		}
	}
	printf("	parent about to wait...");
	wait(NULL);
	printf("	done waiting. returning 1");

	return (1);
}
