#include "main.h"


/**
 * read_from_file - reads input from a file or is passed input
 * @ac: argument count
 * @av: list of arguments
 * @env: the environment variables.
 * @fptr: file pointer
 * Return: nothing, but may exit success of failure.
 */
void read_from_file(int ac, char **av, char **env, FILE *fptr)
{
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL, **envp = envcopy(env);
	int eval = 1, exit_stat = 0;

	(void)ac;
	(void)av;
	do {
		bytes_read = getcmd(&cmdline, &cmdlen, fptr);
		if (bytes_read < 0)
		{
			if (feof(stdin))
			{
				exit_stat = 0;
				break;
			}
		}
		else
		{
			argv = make_tokens(cmdline, " ");
			if (argv == NULL)
				continue;
			exit_stat = is_exit(argv);
			if (exit_stat >= 0)
			{
				free_table(argv);
				break;
			}
			if (exit_stat == -10)
			{
				free_table(argv);
				eval = 1;
				continue;
			}
			eval = evaluate(argv, envp);
			free_table(argv);
		}
	} while (eval == 1);
	cleanup(cmdline, envp);
	exit(exit_stat);
}
