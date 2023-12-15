#include "main.h"


/**
 * main - the shell hell
 */
int main(void)
{
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		file_mode();

	return (0);
}
