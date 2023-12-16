#include "main.h"


/**
 * dump - print simple messages for debugging purposes
 * this function is useless in hindsight but just leave it
 * @str1: string 1
 * @str2: string 2
 * Return: none.
 */
void dump(char *str1, char *str2)
{
	printf("%s", str1);
	printf("%s", str2);
	putchar('\n');
}


/**
 * panic - print error message, clean and return.
 * @msg: perror to print.
 * @str: str to clean.
 * @table: char array to clean.
 * @ret: int to return
 * Return: what user gives.
 */
int panic(char *msg, char *str, char **table, int ret)
{
	perror(msg);
	cleanup(str, table);

	return (ret);
}
