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
	if (isatty(STDIN_FILENO))
		interactive_mode(env);
	else
		file_mode(ac, av, env);

	return (0);
}
