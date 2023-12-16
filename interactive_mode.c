#include "main.h"


/**
 * interactive_mode - REPL
 * @environ: the environment variable
 * Return: nothing, but will exit SUCCESS once done.
 */
void interactive_mode(char **environ)
{
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL, **envp = envcopy(environ);
	int eval = 1;

	do {
		printf("($) ");
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
			eval = 1;
		else
		{
			argv = make_tokens(cmdline, " ");
			if (argv == NULL)
			{
				continue;
			}
			eval = evaluate(argv, envp);
			free_table(argv);
		}
	} while (eval == 1);
	free(cmdline);
}
