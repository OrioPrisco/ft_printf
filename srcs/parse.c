/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:49:30 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 13:46:04 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <ftprintf.h>

static ssize_t	find_and_parse(const char **format, va_list *ap);

static ssize_t (*const	g_print_funcs[])(t_flags, int, int, va_list*) = {
	&ft_printfchar,
	&ft_printfstr,
	&ft_printfptr,
	&ft_printfint,
	&ft_printfint,
	&ft_printfuint,
	&ft_printfhex,
	&ft_printfhexup,
	&ft_printfpercent,
	&ft_printfsize_t,
};

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	bytes_written;
	ssize_t	total_bytes;

	total_bytes = 0;
	va_start(ap, format);
	while (*format)
	{
		bytes_written = find_and_parse(&format, &ap);
		if (bytes_written < 0)
			return (-1);
		total_bytes += bytes_written;
	}
	va_end(ap);
	if (b_write(0, NULL, 0) < 0)
		return (-1);
	return (total_bytes);
}

//parses the numbers, removes some f;ags that override each other
//and call the correct printing function with all the info
static int	parse_and_print(const char **format, va_list *ap,
	t_flags flags, char conversion)
{
	int			field_width;
	int			precision;
	const char	*s;

	field_width = -1;
	precision = -1;
	if (flags & FLAG_FIELD_WIDTH)
	{
		s = *format;
		while (!ft_isdigit(*s) || *s == '0')
			s++;
		field_width = ft_atoi(s);
	}
	if (flags & FLAG_PRECISION)
		precision = ft_atoi(ft_strchr(*format, '.') + 1);
	if (flags & FLAG_PLUS)
		flags &= ~FLAG_SPACE;
	if (flags & FLAG_MINUS)
		flags &= ~FLAG_ZERO;
	*format = ft_strchrnul(*format + (conversion == '%'), conversion) + 1;
	return (g_print_funcs[ft_index(CONVERSIONS, conversion)]
		(flags, precision, field_width, ap));
}

//detect if format follows the format
// [flags (no .)]+ [[any number]+.[any number]+]
//then processes it further
//returns
// -1 on failure
// bytes written
static int	check_format_and_parse(const char **format, size_t n, va_list *ap)
// n is number of bytes in format
{
	size_t	i;
	t_flags	flags;

	flags = FLAG_NONE;
	i = 1;
	while (i < n && ft_strchr(&FLAGS[1], (*format)[i]))
		flags |= char_to_flag((*format)[i++]);
	if (i < n && ft_isdigit((*format)[i]))
		flags |= FLAG_FIELD_WIDTH;
	while (i < n && ft_isdigit((*format)[i]))
		i++;
	if (i < n && (*format)[i] == '.')
		flags |= char_to_flag((*format)[i++]);
	if (flags & FLAG_PRECISION)
		while (i < n && ft_isdigit((*format_str)[i]))
				i++;
	if (!ft_strchr(CONVERSIONS, (*format)[i]))
	{
		if (b_write(1, *format, i) < 0)
			return (-1);
		return (advance_str(format, i));
	}
	return (parse_and_print(format, ap, flags, (*format)[i]));
}

//returns bytes written
//finds something like %[flag or digit]+ [any conversion]
//and processes it further
static ssize_t	find_and_parse(const char **format, va_list *ap)
{
	ssize_t	bytes_written;
	ssize_t	n;

	bytes_written = ft_strchrnul(*format, '%') - *format;
	if (b_write(1, *format, bytes_written) < 0)
		return (-1);
	advance_str(format, bytes_written);
	if (!(**format))
		return (bytes_written);
	n = 1;
	while ((*format)[n] && ft_strchr(FLAGS_NUM, (*format)[n]))
		n++;
	if (!(*format)[n] || !ft_strchr(CONVERSIONS, (*format)[n]))
	{
		if (b_write(1, *format, n) < 0)
			return (-1);
		return (bytes_written + advance_str(format, n));
	}
	n = check_format_and_parse(format, n, ap);
	if (n < 0)
		return (-1);
	return (n + bytes_written);
}
