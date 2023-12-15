#include "main.h"


/**
 * interactive_mode - REPL
 * Return: nothing, but will exit SUCCESS once done.
 */
void interactive_mode(void)
{
	size_t cmdlen = 0;
	ssize_t bytes_read = -1;
	char *cmdline = NULL, **argv = NULL;
	char **envp = envcopy();
	int eval = 1;

	do {
		printf("($) ");
		bytes_read = getcmd(&cmdline, &cmdlen, stdin);
		/* check if nothing was read. there's also double free issue */
		if (bytes_read < 0)
		{
			if (feof(stdin))
			{
				free(cmdline); /* potential segfault? */
				exit(EXIT_SUCCESS);
			}
			else
				perror("Couldn't read input for some reason. Try again.");
		}
		/* useful? else if (bytes_read == 0); */
		else
		{
			/* argv is freed only when it is allocated */
			argv = make_tokens(cmdline, " ");
			printf("*****ARGV[0] FROM MAIN BEFORE:%s\n", argv[0]); /* DEBUG */
			cmd_as_dirs(argv);
			printf("*****ARGV[0] FROM MAIN AFTER:%s\n", argv[0]); /* DEBUG */
			eval = evaluate(argv, envp);
			printf("EVAL EVALUATED AS: %d. ABOUT TO CLEANUP...\n", eval); /* DEBUG */
			free_table(argv); /* the issue is prolly here*/
		}
		/* /free(cmdline);*/
		putchar('\n'); /* DEBUG */
	} while (eval == 1);
	free(cmdline);
}



/**
 * file_mode - reads input from a file or is passed input
 * Return: nothing, but may exit success of failure.
 */
void file_mode(int ac, char **av, char **env)
{
	exit(EXIT_FAILURE);
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
