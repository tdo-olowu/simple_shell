#include "main.h"


/**
 * free_table - frees a null-terminated array of strings
 * @table: an array of strings.
 * Return: none.
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
 * @line: a string.
 * @table: an array of strings.
 * Return: none.
 */
void cleanup(char *line, char **table)
{
	printf("Beginning cleanup..."); /* DEBUG */
	if (line != NULL)
		free(line);
	if (table != NULL)
		free_table(table);
	printf("Concluding cleanup..."); /* DEBUG */
}
