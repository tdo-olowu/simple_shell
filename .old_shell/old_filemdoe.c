#include "main.h"


/**
 * file_mode - reads input from a file or is passed input
 * @ac: argument count
 * @av: list of arguments
 * @env: the environment variables.
 * Return: nothing, but may exit success of failure.
 */
void file_mode(int ac, char **av, char **env)
{
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL, **envp = env;
	int eval = 1;

	do {
		bytes_read = getcmd(&cmdline, &cmdlen, stdin);
		if (bytes_read < 0)
		{
			if (feof(stdin))
			{
				free(cmdline);
				exit(EXIT_SUCCESS);
			}
			else
				perror("Couldn't read input for some reason. Try again.");
		}
		else if (bytes_read == 0)
			eval = -1;
		else
		{
			argv = make_tokens(cmdline, " ");
			eval = evaluate(argv, envp);
			free_table(argv);
		}
		/* /free(cmdline);*/
	} while (eval == 1);
	free(cmdline);
}
