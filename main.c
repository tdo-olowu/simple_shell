#include "main.h"
#include <stdio.h>
#include <unistd.h>
/**
 * interactive_mode - this is the main function.
 * file_mode - this is the main function
 * @argc: a parameter that takes arguments.
 * @argv: a parameter that takes arguments.
 * @envp: a parameter that takes variables.
 * Return: interactive_mode or file_mode.
 */
#define BLANK " "

int interactive_mode(void);
int file_mode(int argc, char *argv[], char *envp[]);

int main(int argc, char *argv[], char *envp[])
{
	if (isatty(STDIN_FILENO))
		return (interactive_mode);
	else
		return (file_mode(argc, argv, envp));
}
