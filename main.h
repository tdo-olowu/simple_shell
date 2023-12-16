#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* type and struct definitions */
typedef struct node dir_type;
typedef struct bins bin_type;

/**
 * struct node - simply linked list
 * @dir: a string holding the directory prefix.
 * @next: pointer to the next node.
 *
 * Description: singly-linked list for PATH
 */
struct node
{
	char *dir;
	dir_type *next;
};

/**
 * struct bins - builtin name and associated function.
 * @name: name of the function as read by hsh
 * @func: the actual function as named in source code.
 *
 * Description: associates names with processes.
 * might include type later, possibly.
 * depends on if I don't die of overwork.
 * only exec_bin will be affected.
 */
struct bins
{
	char *name;
	int (*func)(char **, char **);
};


/* modes */
void interactive_mode(char **);
void file_mode(int, char **, char **);

/* input-output */
ssize_t getcmd(char **, size_t *, FILE *);
size_t count_args(char **);
long int convert_to_int(char *);

/* text parsing and processing */
char **make_tokens(char *, char *);
char **envcopy(char **);
char *cmd_as_dir(char *, char *);
char *genv(char *, char **);

/* path handling */
int is_a_dir(char *);
dir_type *append_dir_node(dir_type **, char *);
dir_type *append_node(dir_type **, char *);
dir_type *build_dir_chain(char **);

/* process_handling */
int evaluate(char **, char **);
int dummy_process(char *, char **, char **);
int file_exists(char *);
int try_paths(void);

/* builtins */
int (*exec_bin(char **, char **))(char **, char **);
int hsh_exit(char **, char **);
int penv(char **, char **);
int hsh_cd(char **, char **);
int is_exit(char **);

/* memory management */
void free_table(char **);
void cleanup(char *, char **);
void free_list(dir_type *);

/* testing and debugging functions */
void dump(char *, char *);
int panic(char *, char *, char **, int);
void pargv(char **);



#endif /* MAIN_H */
