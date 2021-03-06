#ifndef SHELL_H
#define SHELL_H
/* Includes*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
/* STRUCTS */
/**
 * struct linked_list - linked list struct
 * @str: string value
 * @next: next node address
 */
typedef struct linked_list
{
	char *str;
	struct linked_list *next;
} ll;
/**
 * struct myreturns - holds data
 * @alias_List: list of aliases
 * @free_env_list: list of envs to be freed
 */
typedef struct myreturns
{
	ll *alias_List;
	char *free_env_list;
} my_ret;
/**
 * struct built_in - built_in struct
 * @var: built_in command
 * @f: function pointer
 */
typedef struct built_in
{
	char *var;
	char * (*f)(char **cmd_list, ll *alias_list, char *free_env_list,
				char **tokes, char *argv, char **env);
} b_in;
/* Global vars */
extern int errno;
/* Prototypes */
void free_list(ll *head);
char *_strtok(char *str, int *index, char delim);
int _putchar(char c);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(char *str);
void dim2(char *str, int *chars, int *words, char *argv);
my_ret parser2(char **cmd_List, char *argv, char **env, my_ret my_lists);
char **parser1(char *cmd_Str, char *argv);
void StrDimensions(char *cmd_Str, char *argv,
	 int *cmd_Str_Len, int *cmd_Count);
char *read_Cmd(int mode, int *sig);
void exec_Cmd(char **tokes, char *argv, char **env);
char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);
void print_Prompt1(void);
char *str_number(char *buf, unsigned int n);
void print_Prompt2(void);
char *builtin(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env, int *ret);
char *my_exit(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env);
char *get_path(char **env, char *token);
int path_check(char **paths);
char **append_paths(char *token, char **paths);
char *str_mul_cat(char *dest, char *str2, char *str1);
int path_idx(char **env);
size_t get_size(char *str, char delim);
char *_setenv(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env);
char *b_env(char **cmd_list, ll *alias_list,
	    char *free_env_list, char **tokes, char *argv, char **env);
char *_unsetenv(char **cmd_list, ll *alias_list,
		char *free_env_list, char **tokes, char *argv, char **env);
my_ret _script(int fd, char *argv, char **env, my_ret my_lists);
ll *add_Alias(char *token, char *argv, ll *alias_List);
ll *alias_Options(char *argv, char *cmd, ll *alias_List);
void print_Alias(char *token, char *argv, ll *alias_List);
ll *add_Alias_Node(ll **alias_List, char *str);
char *_strtok_Alias(char *str, int *index, char delim);
void dim3(char *str, int *chars, int *words, char *argv);
void print_list(ll *h);
char *_strtok_Alias(char *str, int *index, char delim);
char *alias_Check(char *cmd_Str, ll *alias_List, char *argv);
char *reset_Cmd(char *alias_Cmd, char *argv, char *cmd_Str, int idx, int len);
char *rep_Alias(ll *alias_List, char *argv, char **tokes, int *idx, int *len);
char *print_number(char *str, int n);
void handle_err(char *argv, int err_num, char *token);
char *add_cwd(char *str);
char *_cd(char **cmd_list, ll *alias_list,
	  char *free_env_list, char **tokes, char *argv, char **env);
char *set_pwd(char *str, char **env, char *free_env_list);
void set_old_pwd(char *str, char **env, char *free_env_list);
char *get_old_dir(char *old, char **env);
char *get_home(char *home, char **env);
void free_env(char **env, char *free_env_list);
char *add_to_free_env(char *free_env_list, char *token);
char *remove_free_list_node(char *free_env_list, char *token);
int xstrlen(char *s);
void free_rm(char **cmd, ll *alias_list);
char *_strncpy(char *dest, char *src, int n);
int _strncmp(const char *s1, const char *s2, size_t n);
int myAtoi(char *s);
char *_strcat(char *str, char *str2);
int _strcmp(char *s1, char *s2);
void free_2d(char **arr);
void script_check(int argc, char *argv[], char **env, my_ret my_lists
		  , char **Cmd);
char *comment_check(char *buf);
char *cat_err(char *num, char *argv, char *var, char *token);
char *findcwd(char *buf, size_t n);
char *cwd_cat(char *temp, int idx, char *buf, char *str, int *sig);
char *cat_err2(char *num, char *argv, char *var, char *token);
int quick_stat(char *token);
#endif
