#include "main.h"

/**
 * main - the main control of the simple shell
 * @argc: arguments count.
 * @argv: list of arguments
 * @envp: list of environment variables.
 * Return: 0 for success.
 */
int main(int argc, char **argv, char **envp)
{
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		file_mode(argc, argv, envp);

	return (0);
}
