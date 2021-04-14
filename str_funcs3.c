#include "shell.h"

/**
 * _strncpy - Copies n amount of bytes from src to dest
 * @dest: Copying to
 * @src: Copying from
 * @n: Amount of bytes to copy
 * Return: Copied string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int x = 0;

	while (x < n && src[x])
	{
		dest[x] = src[x];
		x++;
	}
	while (x < n)
	{
		dest[x] = '\0';
		x++;
	}
	return (dest);
}

/**
 * _strncmp - Comapres n amount of bytes between two strings
 * @s1: First string to compare
 * @s2: Second string to compare
 * @n: Amount of bytes to compare
 * Return: < 0 if str1 is less than str2, > 0 if str2 is less than str1,
 * 0 if str1 is equal to str2
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char u1, u2;

	while (n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
	}
	return (0);
}

/**
 * myAtoi - Converts a string to an integer
 * @s: String to convert
 * Return: Converted string
 */

int myAtoi(char *s)
{
	long sign = 1, res = 0, i = 0, answer = 0;

	while (s[i] == ' ')
		i++;

	if (*s == '\0')
		return (-1);

	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	for (; s[i]; i++)
	{
		if (s[i] >= '0' || s[i] <= '9')
			res = res * 10  + s[i] - '0';
		else
			return (-1);
	}
	answer = (sign * res);
	if (answer > INT_MAX && answer < INT_MIN)
		return (-1);
	return (sign * res);
}

/**
 * _strcat - concats strs
 * @str: string 1
 * @str2: string 2
 * Return: concatenated string
 */

char *_strcat(char *str, char *str2)
{
	int x = 0, xx = 0;

	if (!str)
		return (NULL);
	for (x = 0; str[x]; x++)
		;
	for (xx = 0; str2[xx]; xx++)
	{
		str[x] = str2[xx];
		x++;
	}
	str[x] = '\0';
	return (str);
}
