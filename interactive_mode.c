#include "main.h"


/**
 * interactive_mode - REPL
 * @env: the environment variable
 * Return: nothing, but will exit SUCCESS once done.
 */
void interactive_mode(char **env)
{
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL, **ev = envcopy(env);
	int eval = 1, exit_stat = 0;

	do {
		printf("($) ");
		bytes_read = getcmd(&cmdline, &cmdlen, stdin);
		if (bytes_read < 0)
		{
			if (feof(stdin))
				break;
			perror("Couldn't read input for some reason. Try again");
		}
		else if (bytes_read == 0)
		{
			eval = 1;
			continue;
		}
		else
		{
			argv = make_tokens(cmdline, " ");
			if (argv == NULL)
			{
				eval = 1;
				continue;
			}
			exit_stat = is_exit(argv);
			if (exit_stat >= 0)
			{
				printf("exit_stat: %d\n", exit_stat);
				free_table(argv);
				break;
			}
			if (exit_stat == -10)
			{
				printf("exit_stat: %d\n", exit_stat);
				free_table(argv);
				eval = 1;
				continue;
			}
			eval = evaluate(argv, ev);
			free_table(argv);
		}
	} while (eval == 1);
	free(cmdline);
	free_table(ev);
	exit(exit_stat);
}
