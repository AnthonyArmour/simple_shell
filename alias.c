#include "shell.h"

/**
 * add_Alias - Calls add_Alias_node
 * @token: token
 * @argv: argv[0]
 * @alias_List: list of aliases
 * Return: alias_List
 */

ll *add_Alias(char *token, char *argv, ll *alias_List)
{
	(void)argv;


	alias_List = add_Alias_Node(&alias_List, token);
	return (alias_List);
}

/**
 * print_Alias - prints alias
 * @token: alias to print
 * @argv: argv[0]
 * @alias_List: alias list
 * Return: void
 */

void print_Alias(char *token, char *argv, ll *alias_List)
{
	int signal = 0;

	strcat(token, "=");
	(void)argv;
	while (alias_List->next != NULL)
	{
		if ((strncmp(alias_List->str, token, _strlen(token))) == 0)
		{
			write(STDOUT_FILENO, alias_List->str, _strlen(alias_List->str));
			write(STDOUT_FILENO, "\n", 1);
			signal++;
			break;
		}
		else
			alias_List = alias_List->next;
	}
	if (alias_List->next == NULL)
	{
		if ((strncmp(alias_List->str, token, _strlen(token))) == 0)
		{
			write(STDOUT_FILENO, alias_List->str, _strlen(alias_List->str));
			write(STDOUT_FILENO, "\n", 1);
			signal++;
		}
	}
	if (signal == 0)
		printf("OOPSIES\n");
}


/**
 * add_Alias_node - adds node
 * @alias_List: list of aliases
 * @str: ptr
 * Return: list_t ptr
 */

ll *add_Alias_Node(ll **alias_List, char *str)
{
	ll *temp;

	if (str == NULL)
		return (NULL);
	temp = malloc(sizeof(ll));
	if (temp == NULL)
		return (NULL);
	temp->str = _strdup(str);
	if (temp->str == NULL)
	{
		free(temp);
		return (NULL);
	}
	temp->next = *alias_List;
	*alias_List = temp;
	return (*alias_List);
}

/**
 * free_list - frees lists
 * @head: head of list
 * Return: void
 */

void free_list(ll *head)
{
	ll *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

/**
 * print_list - prints linked list
 * @h: head of list
 * Return: void
 */

void print_list(ll *h)
{
	while (h->next != NULL)
	{
		write(STDOUT_FILENO, h->str, _strlen(h->str));
		h = h->next;
	}
	write(STDOUT_FILENO, h->str, _strlen(h->str));
}
