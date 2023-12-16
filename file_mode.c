#include "main.h"


/**
 * file_mode - reads input from a file or is passed input
 * Return: nothing, but may exit success of failure.
 */
void file_mode(int ac, char **av, char **env)
{
	char *prog_name = av[0];
	char *cmd_name = ((ac >= 2) ? av[1] : NULL);
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL;
	char **envp = env;
	int eval = 1;

	do {
		bytes_read = getcmd(&cmdline, &cmdlen, stdin);
		if (bytes_read < 0)
		{
			if (feof(stdin))
			{
				free(cmdline);
				exit(EXIT_SUCCESS);
			}
			else
				perror("Couldn't read input for some reason. Try again.");
		}
		else if (bytes_read == 0)
			eval = -1;
		else
		{
			argv = make_tokens(cmdline, " ");
			eval = evaluate(argv, envp);
			free_table(argv);
		}
		/* /free(cmdline);*/
	} while (eval == 1);
	free(cmdline);

	(void)prog_name;
	(void)cmd_name;
}

/**
 * CGPT's filemode code. Sorry, but I'm desperate.
 * void file_mode(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t cmdlen = 0;
    char *cmdline = NULL, **argv = NULL;
    char **envp = envcopy();

    while (getline(&cmdline, &cmdlen, file) != -1) {
        // Remove newline character from the end of the line
        size_t len = strlen(cmdline);
        if (len > 0 && cmdline[len - 1] == '\n') {
            cmdline[len - 1] = '\0';
        }

        // Tokenize and execute the command
        argv = make_tokens(cmdline, " ");
        printf("Executing command: %s\n", cmdline);
        evaluate(argv, envp);

        // Cleanup for the next iteration
        cleanup(cmdline, argv);
    }

    // Cleanup at the end
    fclose(file);
    cleanup(cmdline, argv);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    file_mode(argv[1]);

    return EXIT_SUCCESS;
}
*/
