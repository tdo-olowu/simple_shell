#include "main.h"
#include <stdio.h>
#include <unistd.h>

#define BLANK " "

int interactive_mode(void);
int file_mode(int argc, char *argv[], char *envp[]);

int main(int argc, char *argv[], char *envp[])
{
	if (isatty(STDIN_FILENO))
		return (interactive_mode);
	else
		return file_mode(argc, argv, envp);
}
