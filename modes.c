#include "main.h"

#define BLANK " "

/**
 * interactive_mode - interact with shell via terminal
 * Return: none
 */
void interactive_mode(void)
{
	char *ps = "($)";
	char *response = NULL;
	char **argv = NULL;

	size_t rlen = 0;
	int repl = 1;
	ssize_t bytes_read;
	extern char **environ;

	do {
		printf("%s ", ps);
		bytes_read = getcmd(&response, &rlen, stdin);
		if (bytes_read < 0)
		{
			if (feof(stdin))
				repl = -1;
			else
				perror("hsh: couldn't read line");
		}
		else
		{
			argv = tokenify(response, BLANK);
			if (argv == NULL)
				perror("couldn't parse input");
			else
				repl = evaluate(argv, environ);
		}
		cleanup(response, argv, NULL);
	} while (repl >= 0);
	exit(EXIT_SUCCESS);
}


/**
 * file_mode - shell is used as a cmd in terminal
 * @argc: argument count
 * @argv: list of arguments
 * @envp: list of environment variables.
 * Return: none.
 */
void file_mode(int argc, char **argv, char **envp)
{
	char *response = NULL;
	size_t rlen = 0;
	int repl = 1;
	ssize_t bytes_read;

	argc -= 1;
	do {
		bytes_read = getcmd(&response, &rlen, stdin);
		/* don't bother processing if line is comment line. */
		if (bytes_read < 0)
		{
			if (feof(stdin))
				repl = -1;
			else
				perror("hsh: couldn't read line");
		}
		else
		{
			argv = tokenify(response, BLANK);
			if (argv == NULL)
				perror("couldn't parse input");
			else
				repl = evaluate(argv, envp);
		}
		cleanup(response, argv, NULL);
	} while (repl >= 0);
	exit(EXIT_SUCCESS);
}
