#include "main.h"


/**
 * free_table - frees a null-terminated array of strings
 */
void free_table(char **table)
{
	int i;

	if (table != NULL)
	{
		for (i = 0 ; table[i] != NULL ; ++i)
			free(table[i]);
	}
	free(table);
}


/**
 * cleanup - a function for convenience.
 */
void cleanup(char *line, char **table)
{
	printf("Beginning cleanup...");
	if (line != NULL)
		free(line);
	if (table != NULL)
		free_table(table);
	printf("Concluding cleanup...");
}
