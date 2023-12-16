#include "main.h"


/**
 * main - the shell hell
 * code makes it look so simple...
 * @ac: argument count.
 * @av: list of arguments
 * @env: environment variables
 * Return: 0 for success.
 */
int main(int ac, char **av, char **env)
{
	int i;

	for (i = 0 ; env[i] != NULL ; ++i)
		printf("%s\n", env[i]);
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		file_mode(ac, av, env);

	return (0);
}
