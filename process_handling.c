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
	int (*exe)(char **, char **);
	char *path, *msg, **paths, *cmd, *gv;
	dir_type *dir_head, *dir_node;

	exe = exec_bin(argv, envp);
	msg = "Couldn't resolve PATH";
	if (exe == NULL)
	{
		if (*argv == NULL)
			return (1);
		cmd = argv[0];
		if (file_exists(cmd))
			return (dummy_process(cmd, argv, envp));
		gv = genv("PATH", envp);
		paths = make_tokens(gv, ":");
		dir_node = build_dir_chain(paths);
		if (dir_node == NULL)
		{
			perror(msg);
			free_table(paths);
			return (1);
		}
		dir_head = dir_node;
		while (dir_node != NULL)
		{
			path = cmd_as_dir(cmd, dir_node->dir);
			if (path == NULL)
				return (panic(msg, NULL, paths, 1));
			if (file_exists(path))
				return (dummy_process(path, argv, envp));
			dir_node = dir_node->next;
		}
		perror("hsh");
		free_list(dir_head);
		cleanup(gv, paths);
	}
	else
		status = exe(argv, envp);
	return (status);
}


/**
 * try_paths - build a path list and try em all.
 * Return: always returns 1.
 */
int try_paths(void)
{
	return (1);
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
 * file_exists - check if a file exists.
 * @path: filepath.
 * Return: 0 if file doesn't exist, 1 if it exists.
 */
int file_exists(char *path)
{
	int value;
	struct stat buffer;

	value = stat(path, &buffer);
	if (value == 0)
		return (1);
	return (0);
}
