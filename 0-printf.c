#include "main.h"

/**
 * _printf - Use standard output to print an Input
 * @format: The format string
 * Return: The numbers of bytes printed
 */
int _printf(const char *format, ...)
{
	int k = 0;
	va_list ap;
	char *p, *start;

	params_t params = PARAMS_INIT;

	va_start(ap, format);

	if (!format || (format[0] == '%' && !format[1]))/* check for NULL char */
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = (char *)format; *p; p++)
	{
		init_params(&params, ap);
		if (*p != '%')/*check for the % specifier*/
		{
			k += _putchar(*p);
			continue;
		}
		start = p;
		p++;
		while (get_flag(p, &params))
		{
			p++;
		}
		p = get_width(p, &params, ap);
		p = get_precision(p, &params, ap);
		if (get_modifier(p, &params))
			p++;
		if (!get_specifier(p))
			k += print_from_to(start, p,
					params.l_modifier || params.h_modifier ? p - 1 : 0);
		else
			k += get_print_func(p, ap, &params);
	}
	_putchar(BUF_FLUSH);
	va_end(ap);
	return (k);
}
