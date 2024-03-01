#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Read and Write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command Chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Number Conversions() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 When Getline System In Use() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readflds: the flds from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readflds;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop.c */
int hsh(info_t *, char **);
int p_find_builtin(info_t *);
void p_find_cmd(info_t *);
void p_fork_cmd(info_t *);

/* parser.c */
int p_is_cmd(info_t *, char *);
char *p_dup_chars(char *, int, int);
char *p_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void p_eputs(char *);
int p_eputchar(char);
int p_putflds(char c, int flds);
int p_putsflds(char *str, int flds);
int p_erratoi(char *);
void p_print_error(info_t *, char *);
int p_print_d(int, int);
char *p_convert_number(long int, int, int);
void p_remove_comments(char *);

/* toem_string.c */
int p_strlen(char *);
int p_strcmp(char *, char *);
char *p_starts_with(const char *, const char *);
char *p_strcat(char *, char *);

/* toem_string1.c */
char *p_strcpy(char *, char *);
char *p_strdup(const char *);
void p_puts(char *);
int p_putchar(char);

/* exits.c */
char *p_strncpy(char *, char *, int);
char *p_strncat(char *, char *, int);
char *p_strchr(char *, char);

/* tokenizer.c */
char **p_strtow(char *, char *);
char **p_strtow2(char *, char);

/* realloc.c */
char *p_memset(char *, char, unsigned int);
void p_ffree(char **);
void *p_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int p_bfree(void **);

/* atoi.c */
int p_interactive(info_t *);
int p_is_delim(char, char *);
int p_isalpha(int);
int p_atoi(char *);


/* builtin.c */
int p_myexit(info_t *);
int p_mycd(info_t *);
int p_myhelp(info_t *);
int p_myhistory(info_t *);
int p_myalias(info_t *);
int p_unset_alias(info_t *, char *);
int p_set_alias(info_t *, char *);
int p_print_alias(list_t *);
int p_myalias(info_t *);

/* getline.c */
ssize_t p_input_buf(info_t *, char **, size_t *);
ssize_t p_get_input(info_t *);
ssize_t p_read_buf(info_t *, char *, size_t *);
int p_getline(info_t *, char **, size_t *);
void p_sigintHandler(int);

/* getinfo.c */
void p_clear_info(info_t *);
void p_set_info(info_t *, char **);
void p_free_info(info_t *, int);

/* environ.c */
char *p_getenv(info_t *, const char *);
int p_myenv(info_t *);
int p_mysetenv(info_t *);
int p_myunsetenv(info_t *);
int p_populate_env_list(info_t *);

/* getenv.c */
char **p_get_environ(info_t *);
int p_unsetenv(info_t *, char *);
int p_setenv(info_t *, char *, char *);

/* history.c */
char *p_get_history_file(info_t *info);
int p_write_history(info_t *info);
int p_read_history(info_t *info);
int p_build_history_list(info_t *info, char *buf, int linecount);
int p_renumber_history(info_t *info);

/* lists.c */
list_t *p_add_node(list_t **, const char *, int);
list_t *p_add_node_end(list_t **, const char *, int);
size_t p_print_list_str(const list_t *);
int p_delete_node_at_index(list_t **, unsigned int);
void p_free_list(list_t **);
size_t p_list_len(const list_t *);
char **p_list_to_strings(list_t *);
size_t p_print_list(const list_t *);
list_t *p_node_starts_with(list_t *, char *, char);
ssize_t p_get_node_index(list_t *, list_t *);

/* vars.c */
int p_is_chain(info_t *, char *, size_t *);
void p_check_chain(info_t *, char *, size_t *, size_t, size_t);
int p_replace_alias(info_t *);
int p_replace_vars(info_t *);
int p_replace_string(char **, char *);

#endif
