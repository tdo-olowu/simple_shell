#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/* modes */
void interactive_mode(void);
void file_mode(int, char**, char**);


/* important variables */
char *PROMPT = "($) ";
typedef struct node path_list;
typedef struct bins bin_t;
struct node {
	char *dir;
	path_list *next;
};
struct bins {
	char *name;
	int (*f)(void*);
};


/* input acquisition */
void prompt(char*);
ssize_t getcmd(char**, size_t*, FILE*);
char *genv(char*);

/* process control */
int execute(char*, char**, char**);
int evaluate(char**, char**);
int (*search_bins(char*))(void*);
int attempt(char**, char**);

/* builtins */
int leave(void*);
int _env(void*);

/* input parsing */
char **tokenify(char*, char*);
char *pathify(char*, char*);
path_list *path_chain(char *paths);
char *joinstr(char*, char*);

/* memory management */
void free_table(char**);
void free_links(path_list*);
void cleanup(char*, char**, path_list*);

/* builtins */
/* file and directory navigation */


#endif /* MAIN_H */
