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
#include <unistd.h>

static ssize_t	find_and_parse(int fd, const char **format, va_list *ap);

static ssize_t (*const	g_print_funcs[])(t_format*, va_list*) = {
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
		bytes_written = find_and_parse(STDOUT_FILENO, &format, &ap);
		if (bytes_written < 0)
			return (-1);
		total_bytes += bytes_written;
	}
	va_end(ap);
	if (b_write(FLUSH_BUFFER, NULL, 0) < 0)
		return (-1);
	return (total_bytes);
}

//parses the numbers, removes some f;ags that override each other
//and call the correct printing function with all the info
static int	parse_and_print(const char **format_str, va_list *ap,
	t_format *format)
{
	const char	*s;

	format->width = -1;
	format->precision = -1;
	if (format->flags & FLAG_FIELD_WIDTH)
	{
		s = *format_str;
		while (!ft_isdigit(*s) || *s == '0')
			s++;
		format->width = ft_atoi(s);
	}
	if (format->flags & FLAG_PRECISION)
		format->precision = ft_atoi(ft_strchr(*format_str, '.') + 1);
	if (format->flags & FLAG_PLUS)
		format->flags &= ~FLAG_SPACE;
	if (format->flags & FLAG_MINUS)
		format->flags &= ~FLAG_ZERO;
	*format_str = ft_strchrnul(*format_str + (format->conversion == '%'),
			format->conversion) + 1;
	return (g_print_funcs[ft_index(CONVERSIONS, format->conversion)]
		(format, ap));
}

//detect if format follows the format
// [flags (no .)]+ [[any number]+.[any number]+]
//then processes it further
//returns
// -1 on failure
// bytes written
// n is number of bytes in format
static int	check_format_and_parse(int fd, const char **format_str,
	size_t n, va_list *ap)
{
	size_t		i;
	t_format	format;

	ft_bzero(&format, sizeof(format));
	i = 1;
	format.fd = fd;
	while (i < n && ft_strchr(&FLAGS[1], (*format_str)[i]))
		format.flags |= char_to_flag((*format_str)[i++]);
	if (i < n && ft_isdigit((*format_str)[i]))
		format.flags |= FLAG_FIELD_WIDTH;
	while (i < n && ft_isdigit((*format_str)[i]))
		i++;
	if (i < n && (*format_str)[i] == '.')
		format.flags |= char_to_flag((*format_str)[i++]);
	if (format.flags & FLAG_PRECISION)
		while (i < n && ft_isdigit((*format_str)[i]))
				i++;
	if (!ft_strchr(CONVERSIONS, (*format_str)[i]))
	{
		if (b_write(fd, *format_str, i) < 0)
			return (-1);
		return (advance_str(format_str, i));
	}
	format.conversion = (*format_str)[i];
	return (parse_and_print(format_str, ap, &format));
}

//returns bytes written
//finds something like %[flag or digit]+ [any conversion]
//and processes it further
static ssize_t	find_and_parse(int fd, const char **format, va_list *ap)
{
	ssize_t	bytes_written;
	ssize_t	n;

	bytes_written = ft_strchrnul(*format, '%') - *format;
	if (b_write(fd, *format, bytes_written) < 0)
		return (-1);
	advance_str(format, bytes_written);
	if (!(**format))
		return (bytes_written);
	n = 1;
	while ((*format)[n] && ft_strchr(FLAGS_NUM, (*format)[n]))
		n++;
	if (!(*format)[n] || !ft_strchr(CONVERSIONS, (*format)[n]))
	{
		if (b_write(fd, *format, n) < 0)
			return (-1);
		return (bytes_written + advance_str(format, n));
	}
	n = check_format_and_parse(fd, format, n, ap);
	if (n < 0)
		return (-1);
	return (n + bytes_written);
}
