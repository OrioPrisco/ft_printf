/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:49:30 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/15 16:10:49 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <unistd.h>
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
	&ft_printfhexup
};

int	ftprintf(const char *format, ...)
{
	va_list	ap;
	size_t	bytes_written;
	size_t	total_bytes;

	total_bytes = 0;
	va_start(ap, format);
	while (0)
	{
	}
	bytes_written = find_and_parse(&format, &ap);
	if (bytes_written < 0)
		return (-1);
	va_end(ap);
	return (bytes_written);
}

//parses the numbers, removes some f;ags that override each other
//and call the correct printing function with all the info
static int	parse_and_print(char *format, va_list *ap,
	t_flags flags, char conversion)
{
	int		field_width;
	int		precision;
	char	*s;

	field_width = -1;
	precision = -1;
	if (flags & FLAG_FIELD_WIDTH)
	{
		s = ft_strchrnul(format, '.');
		while (!ft_isdigit(*s))
			s--;
		while (ft_isdigit(*s))
			s--;
		field_width = ft_atoi(++s);
	}
	if (flags & FLAG_PRECISION)
		precision = ft_atoi(ft_strchr(format, '.') + 1);
	if (flags && FLAG_PLUS)
		flags &= ~FLAG_SPACE;
	if (flags & FLAG_MINUS)
		flags &= ~FLAG_ZERO;
	return (g_print_funcs[ft_index(CONVERSIONS, conversion)]
		(flags, precision, field_width, ap));
}

//detect if format follows the format
// [flags (no .)]+ [[any number]+.[any number]+]
//then processes it further
//returns
// -1 on failure
// bytes written
static int	check_format_and_parse(char *format, size_t n, va_list *ap)
{
	size_t	i;
	t_flags	flags;

	flags = 0;
	i = 1;
	if (i < n)
	{
		while (i < n && ft_strchr(&FLAGS[1], format[i]))
			flags |= char_to_flag(format[i++]);
		while (i < n && ft_isdigit(format[i]))
		{
			flags |= FLAG_FIELD_WIDTH;
			i++;
		}
		if (i < n && format[i] == '.')
		{
			flags |= char_to_flag(format[i++]);
			while (i < n && ft_isdigit(format[i]))
				i++;
		}
	}
	if (!ft_strchr(CONVERSIONS, format[i]))
		return (0);
	return (parse_and_print(format, ap, flags, format[i]));
}

//returns bytes written
//finds something like %[flag or digit]+ [any conversion]
//and processes it further
static ssize_t	find_and_parse(const char **format, va_list *ap)
{
	ssize_t	bytes_written;
	size_t	n;
	char	*s;

	s = ft_strchrnul(*format, '%');
	if (write(1, format, s - *format) < 0)
		return (-1);
	if (!*s)
		return (s - *format);
	n = 1;
	while (s[n] && ft_strchr(FLAGS_NUM, s[n]))
		n++;
	if (!ft_strchr(CONVERSIONS, s[n]))
	{
		if (write(1, s, n) < 0)
			return (-1);
		return (s - *format + n);
	}
	bytes_written = check_format_and_parse(s, n, ap);
	if (bytes_written < 0)
		return (-1);
	return (bytes_written + (s - *format));
}
