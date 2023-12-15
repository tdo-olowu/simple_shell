#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* type and struct definitions */
typedef struct node dir_type;

/**
 * struct node - simply linked list
 * @dir: a string holding the directory prefix.
 * @next: pointer to the next node.
 *
 * Description: singly-linked list for PATH
 */
struct node {
	char *dir;
	dir_type *next;
};


/* modes */
void interactive_mode(void);
void file_mode(int, char**, char**);

/* input-output */
ssize_t getcmd(char**, size_t*, FILE*);

/* text parsing and processing */
char **make_tokens(char*, char*);
char **envcopy(void);
void cmd_as_dirs(char**);

/* path handling */
dir_type *append_dir_node(dir_type**, char*);
dir_type *append_node(dir_type**, char*);
dir_type *build_dir_chain(char**);

/* process_handling */
int evaluate(char**, char**);
int dummy_process(char**, char**);

/* builtins */
int exec_bin(char**, char**);
int hsh_exit(void);
void penv(char**);

/* memory management */
void free_table(char**);
void cleanup(char*, char**);
void free_list(dir_type*);

/* testing and debugging functions */
void dump(char*, char*);



#endif /* MAIN_H */
