#include "main.h"


/**
 * main - the shell hell
 * code makes it look so simple...
 * Return: 0 for success.
 */
int main(int ac, char **av, char **env)
{
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		file_mode(ac, av, env);

	return (0);
}
