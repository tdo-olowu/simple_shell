#include "main.h"


/**
 * evaluate - execute a list of commands.
 * @argv: a command followed by its arguments.
 * @envp: environment variables.
 * Return: returns -1 if command is exit, returns 1 else.
 */
int evaluate(char **argv, char **envp)
{
	int status = 1;
	int (*exe)(void);
	char *path, *pvalue, *msg, *cmd = argv[0];
	char **paths;
	dir_type *dir_head, *dir_node;

	printf("In function evaluate\n");
	exe = exec_bin(argv, envp);
	msg = "Couldn't resolve PATH";
	if (exe == NULL)
	{
		printf("Not a builtin cmd.\n");
		pvalue = genv("PATH");

		if (pvalue == NULL)
			return (panic(msg, NULL, NULL, 1));
		paths = make_tokens(pvalue, ":");
		if (paths == NULL)
		{
			perror("paths no exist");
			return (panic(msg, NULL, NULL, 1));
		}
		dir_node = build_dir_chain(paths);
		if (dir_node == NULL)
		{
			perror("dirnode is NULL");
			return (panic(msg, NULL, paths, 1));
		}

		/* save this. note - could implement free directly */
		dir_head = dir_node;
		while (dir_node != NULL)
		{
			printf("dir_node is NOT NULL\n");
			path = cmd_as_dir(cmd, dir_node->dir);
			if (path == NULL)
				return (panic(msg, NULL, paths, 1));
			/* does the file exist? */
			/* try just one file. our job is not to try every */
			if (file_exists(path))
			{
				printf("Filefound: %s\n", path); /* DEBUG */
				status = dummy_process(path, argv, envp);
				break;
			}
			dir_node = dir_node->next;
		}
		printf("About to free the dir_list\n");
		free_list(dir_head);
		printf("dir list freedd. about to free paths.\n");
		free_table(paths);
		printf("paths freed.\n");
	}
	else
		status = exe();
	printf("leaving function evaluate...\n");

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

	printf("Inside dummy rpocess\n");
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
 * file_exists - check if a file exists.
 * @path: filepath.
 * Return: 0 if file doesn't exist, 1 if it exists.
 */
int file_exists(char *path)
{
	int value;
	struct stat buffer;

	printf("Checking if file exists.\n");
	value = stat(path, &buffer);
	if (value == 0)
		return (1);
	return (0);
}


/**
 * if (WIFEXITED(exe) && WEXITSTATUS(exe) == EXIT_SUCCESS)
 * 	child succeeded.
 * else
 * 	child failed to execute.
 */
