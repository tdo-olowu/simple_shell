#ifndef MAIN_H
#define MAIN_H

/* Struct for linked list node */
typedef struct path_list
{
	char *dir;
	struct path_list *next;
} path_list;

/* Function prototypes */
void free_table(char **tokens);
void free_links(path_list *head);
void cleanup(char *buffer, char **tokens, path_list *head);

#endif
