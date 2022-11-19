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

int	ftprintf(char *s, ...)
{
	va_list	ap;
	size_t	bytes_written;
	size_t	total_bytes;

	total_bytes = 0;
	va_start(ap, s);
//	while (1)
//	{
		bytes_written = find_parseable(s, &ap);
		if (bytes_written < 0)
			return (-1);
//	}
	va_end(ap);
	return (bytes_written);
}

//aside from field width, could do some 1 << g_flags - strchr(g_flags, c)
static t_flags	char_to_flag(char c)
{
	if (c == '0')
		return (FLAG_ZERO);
	if (c == ' ')
		return (FLAG_SPACE);
	if (c == '#')
		return (FLAG_HASH);
	if (c == '+')
		return (FLAG_PLUS);
	if (c == '-')
		return (FLAG_MINUS);
	if (ft_isdigit(c))
		return (FLAG_FIELD_WIDTH);
	if (c == '.')
		return (FLAG_PRECISION);
	return (FLAG_NONE);
}

static int	parse(char *str, va_list *ap, t_flags flags, char conversion)
{
	int		field_width;
	int		precision;
	char	*s;

	field_width = -1;
	precision = -1;
	if (flags & FLAG_FIELD_WIDTH)
	{
		s = ft_strchrnul(str, '.');
		while (!ft_isdigit(*s))
			s--;
		while (ft_isdigit(*s))
			s--;
		field_width = ft_atoi(++s);
	}
	if (flags & FLAG_PRECISION)
		precision = ft_atoi(ft_strchr(str, '.') + 1);
	if (flags && FLAG_PLUS)
		flags &= ~FLAG_SPACE;
	if (flags & FLAG_MINUS)
		flags &= ~FLAG_ZERO;
	return (g_print_funcs[ft_index(CONVERSIONS, conversion)]
		(flags, precision, field_width, ap));
}

// any of flags (no .) [[any number]+.[any number]+]
//returns
// -1 on failure
// bytes written
static int	check_format(char *str, size_t n, va_list *ap)
{
	size_t	i;
	t_flags	flags;

	flags = 0;
	i = 1;
	while (i < n)
	{
		while (i < n && ft_strchr(&FLAGS[1], str[i]))
			flags |= char_to_flag(str[i++]);
		while (i < n && ft_isdigit(str[i]))
		{
			flags |= FLAG_FIELD_WIDTH;
			i++;
		}
		if (i < n && str[i] == '.')
			flags |= char_to_flag(str[i++]);
	}
	if (!ft_strchr(CONVERSIONS, str[i]))
		return (0);
	return (parse(str, ap, flags, str[i]));
}

//returns bytes written
int	find_parseable(char *str, va_list *ap)
{
	size_t	n;
	char	*begin;

	begin = ft_strchrnul(str, '%');
	write(1, str, begin - str);
	if (!*begin)
		return (begin - str);
	n = 1;
	while (begin[n] && ft_strchr(FLAGS_NUM, begin[n]))
		n++;
	if (!ft_strchr(CONVERSIONS, begin[n]))
	{
		return (begin - str + write(1, begin, n));
	}
	return (check_format(begin, n, ap) + (begin - str));
}
