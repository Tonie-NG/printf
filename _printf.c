#include "main.h"

void print_buffer(char buffer[], int *buff_indicator);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_characters = 0;
	int flags, width, precision, size, buff_indicator = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_indicator++] = format[i];
			if (buff_indicator == BUFF_SIZE)
				print_buffer(buffer, &buff_indicator);
			/* write(1, &format[i], 1);*/
			printed_characters++;
		}
		else
		{
			print_buffer(buffer, &buff_indicator);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_characters += printed;
		}
	}

	print_buffer(buffer, &buff_indicator);

	va_end(list);

	return (printed_characters);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_indicator: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_indicator)
{
	if (*buff_indicator > 0)
		write(1, &buffer[0], *buff_indicator);

	*buff_indicator = 0;
}
