#include "main.h"


/**
 * main - the shell hell
 * code makes it look so simple...
 * Return: 0 for success.
 */
int main(void)
{
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		file_mode();

	return (0);
}
