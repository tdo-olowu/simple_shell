#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/* modes */
void interactive_mode(void);
void file_mode(void);

/* input-output */
ssize_t getcmd(char**, size_t*, FILE*);

/* text parsing and processing */
char **make_tokens(char*, char*);
char **envcopy(void);
void cmd_as_dirs(char**);

/* process_handling */
int evaluate(char**, char**);

/* memory management */
void free_table(char**);
void cleanup(char*, char**);

/* testing and debugging functions */
void dump(char*, char*);



#endif /* MAIN_H */
