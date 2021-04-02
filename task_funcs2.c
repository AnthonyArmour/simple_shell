#include "shell.h"
/**
 * list_len - finds num of elements in list
 * @h: ptr
 * Return: size_t
 */
/*size_t list_len(const list_t *h)
{
	size_t count = 0;

	if (h == NULL)
		return (count);
	while (h->next != NULL)
	{
		count++;
		h = h->next;
	}
	count++;
	return (count);
	}*/
/**
 * add_node - adds node
 * @head: ptr
 * @str: ptr
 * Return: list_t ptr
 */
/*list_t *add_node(list_t **head, const char *str)
{
	list_t *temp;

	if (str == NULL)
		return (NULL);
	temp = malloc(sizeof(list_t));
	if (temp == NULL)
		return (NULL);
	temp->str = strdup((char *)str);
	if (temp->str == NULL)
	{
		free(temp);
		return (NULL);
	}
	temp->len = (unsigned int)_strlen(temp->str);
	temp->next = *head;
	*head = temp;
	return (*head);
	}*/
/**
 * append_text_to_file - appends text to file
 * @filename: name
 * @text_content: str
 * Return: 1 or -1
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fp;
	ssize_t wcheck;

	if (!filename)
		return (-1);
	fp = open(filename, O_WRONLY | O_APPEND);
	if (fp == -1 || fp == EACCES)
		return (-1);
	if (!text_content)
	{
		close(fp);
		return (1);
	}
	wcheck = write(fp, text_content, _strlen(text_content));
	if (wcheck == -1)
	{
		close(fp);
		return (-1);
	}
	close(fp);
	return (1);
}
/**
 * get_nodeint_at_index - return nth node
 * @head: head
 * @index: index of node
 * Return: ptr to node
 */
/*listint_t *get_nodeint_at_index(listint_t *head, unsigned int index)
{
	listint_t *temp;
	unsigned int x = 0;

	if (!head)
		return (NULL);
	temp = head;
	for (x = 0; x < index; x++)
	{
		if ((x + 1) < index && temp->next == NULL)
		{
			return (NULL);
		}
		temp = temp->next;
	}
	return (temp);
	}*/
/**
 * insert_nodeint_at_index - inserts node into linked list
 * @head: head of list
 * @idx: index where node is added
 * @n: data to be stored in new node
 * Return: address of new node
 */
/*listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
{
	listint_t *temp;
	listint_t *trav;
	unsigned int x = 0, y = 0;

	trav = *head;
	while (trav)
	{
		y++;
		trav = trav->next;
	}
	if (idx > y)
		return (NULL);
	temp = malloc(sizeof(listint_t));
	if (!temp)
		return (NULL);
	temp->n = n;
	temp->next = NULL;
	if (!*head)
	{
		*head = temp;
		return (temp);
	}
	if (idx == 0)
	{
		temp->next = *head;
		*head = temp;
		return (temp);
	}
	trav = *head;
	for (x = 0; x < (idx - 1); x++)
		trav = trav->next;
	temp->next = trav->next;
	trav->next = temp;
	return (temp);
	}*/
