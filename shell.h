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
typedef struct linked_list
{
        char *str;
        struct linked_list *next;
} ll;
typedef struct built_in
{
	char *var;
	char * (*f)(char **cmd_list, ll *alias_list, char *free_env_list, char **tokes, char *argv, char **env);
} b_in;
/*typedef struct linked_list
{
	char *str;
	struct linked_list *next;
	} ll;*/
/* Prototypes */
void free_list(ll *head);
char *_strtok(char *str, int *index, char delim);
int _putchar(char c);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(char *str);
void dim2(char *str, int *chars, int *words, char *argv);
ll *parser2(char **cmd_List, char *argv, char **env, ll *alias_List);
char **parser1(char *cmd_Str, char *argv);
void StrDimensions(char *cmd_Str, char *argv, int *cmd_Str_Len, int *cmd_Count);
char *read_Cmd(char *argv);
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
ll *_script(int fd, char *argv, char **env, ll *alias_List);
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
char *print_number(int n);
void handle_err(char *argv, int err_num, char *token);
char *add_cwd(char *str);
char *_cd(char **cmd_list, ll *alias_list,
	  char *free_env_list, char **tokes, char *argv, char **env);
char *set_pwd(char *str, char **env);
void set_old_pwd(char *str, char **env);
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
/*size_t list_len(const list_t *h);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index);
int append_text_to_file(const char *filename, char *text_content);
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n);
*/
#endif
