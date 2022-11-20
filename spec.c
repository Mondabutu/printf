#include "main.h"

/**
 * get_specifier - finds the format function
 * @s: string format
 * Return: the number of bytes printed
 */

int (*get_specifier(char *s))(va_list ap, params_t *params)

{
	specifier_t specifiers[] = {
		{"c", print_char},
		{"d", print_int},
		{"i", print_int},
		{"s", print_string},
		{"%", print_percent},
		{"b", print_binary},
		{"o", print_octal},
		{"u", print_unsigned},
		{"x", print_hex},
		{"X", print_HEX},
		{"p", print_address},
		{"S", print_S},
		{"r", print_rev},
		{"R", print_rot13},
		{NULL, NULL}
	};

	int k = 0;

	while (specifiers[k].specifier)
	{
		if (*s == specifiers[k].specifier[0])
		{
			return (specifiers[k].f);
		}
		k++;
	}
	return (NULL);
}

/**
 * get_print_func - finds the format function
 * @s: string  format
 * @ap: argument pointer
 * @params: the parameters struct
 * Return: the number of bytes printed
 */

int get_print_func(char *s, va_list ap, params_t *params)
{
	int (*f)(va_list, params_t *) = get_specifier(s);

	if (f)
		return (f(ap, params));
	return (0);
}

/**
 * get_flag - finds the flag functions
 * @s: the format string
 * @params: the parameters struct
 * Return: valid flag 
 */

int get_flag(char *s, params_t *params)

{
	int k = 0;

	switch (*s)
	{
		case '+':
			k = params->plus_flag = 1;
			break;
		case ' ':
			k = params->space_flag = 1;
			break;
		case '#':
			k = params->hashtag_flag = 1;
			break;
		case '-':
			k = params->minus_flag = 1;
			break;
		case '0':
			k = params->zero_flag = 1;
			break;
	}
	return (k);
}

/**
 * get_modifier - finds the modifier function
 * @s: string for format
 * @params: parameter structure
 * Return: valid modifier 
 */

int get_modifier(char *s, params_t *params)
{
	int k = 0;

	switch (*s)
	{
		case 'h':
			k = params->h_modifier = 1;
			break;
		case 'l':
			k = params->l_modifier = 1;
			break;
	}
	return (k);
}

/**
 * get_width - gets the width from the format string
 * @s: the format string
 * @params: the parameters struct
 * @ap: the argument pointer
 * Return: the new pointer
 */

char *get_width(char *s, params_t *params, va_list ap)

	/* this function use char **s and modify the pointer? */
{
	int d = 0;

	if (*s == '*')
	{
		d = va_arg(ap, int);
		s++;
	}
	else
	{
		while (_isdigit(*s))
			d = d * 10 + (*s++ - '0');
	}
	params->width = d;
	return (s);
}
