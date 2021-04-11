#include "shell.h"

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
		if (h->str == NULL)
		{
			printf("[0] (nil)\n");
		}
		else
			printf("%s\n", h->str);
		h = h->next;
	}
	printf("%s\n", h->str);
}
