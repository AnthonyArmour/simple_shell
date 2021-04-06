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
/* global variables */
/* Prototypes */
int _putchar(char c);
char *_strcpy(char *dest, char *src);
/*listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n);
 */int _strlen(char *s);
/*size_t list_len(const list_t *h);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index);
int append_text_to_file(const char *filename, char *text_content);
*/char *_strdup(char *str);
char **parser1(char *cmd_Str, char *argv);
void cmdStrDimensions(char *cmd_Str, char *argv, int *cmd_Str_Len, int *cmd_Count);
char *read_Cmd(char *argv);
char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);
char *_strcat(char *dest, char *src);
void print_Prompt1(void);
char *str_number(char *buf, unsigned int n);
void print_Prompt2(void);
#endif
