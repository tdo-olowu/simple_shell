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



/**
 * print_list - prints the elements of a linked list
 * @h: the head of the list.
 * Return: the number of nodes.
 *
size_t print_list(const list_t *h)
{
	const list_t *nodeptr = h;
	int count = 0;
	char *strptr = NULL;

	while (nodeptr != NULL)
	{
		strptr = nodeptr->str;
		if (strptr != NULL)
			printf("[%d] %s\n", nodeptr->len, strptr);
		else
			printf("[0] (nil)\n");
		++count;
		nodeptr = nodeptr->next;
	}

	return ((size_t)count);
}
*/
