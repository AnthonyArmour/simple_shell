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
/* STRUCTS */
typedef struct built_in
{
	char *var;
	int (*f)(char **tokes, char *argv, char **env);
} b_in;
typedef struct linked_list
{
	char *str;
	struct linked_list *next;
} ll;
/* Prototypes */
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
char *_strcat(char *dest, char *src);
void print_Prompt1(void);
char *str_number(char *buf, unsigned int n);
void print_Prompt2(void);
int builtin(char **tokes, char *argv, char **env);
int my_exit(char **tokes, char *argv, char **env);
char *get_path(char **env, char *token);
int path_check(char **paths);
char **append_paths(char *token, char **paths);
char *str_mul_cat(char *dest, char *str2, char *str1);
int path_idx(char **env);
size_t get_size(char *str, char delim);
int _setenv(char **tokes, char *argv, char **env);
int b_env(char **tokes, char *argv, char **env);
int _unsetenv(char **tokes, char *argv, char **env);
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
/*size_t list_len(const list_t *h);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index);
int append_text_to_file(const char *filename, char *text_content);
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n);
*/
#endif
