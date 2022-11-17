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

//'.' has to be the first char because of implentation details
static const char	*g_flags = ".0 #+-";
static const char	*g_flags_num = ". #+-0123456789";
static const char	*g_conversions = "cspdiuxX%";
static int (*const	g_print_funcs[])(t_flags, int, int, va_list*) = {};

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
		s = ft_strchr(str, '.') - 1;
		while (ft_isdigit(*s))
			s--;
		field_width = ft_atoi(++s);
	}
	if (flags & FLAG_PRECISION)
		precision = ft_atoi(ft_strchr(s, '.') + 1);
	return (g_print_funcs[g_conversions - ft_strchr(g_conversions, conversion)]
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
		while (i < n && ft_strchr(g_flags + 1, str[i]))
			flags += char_to_flag(str[i++]);
		while (i < n && ft_isdigit(str[i]))
			flags += char_to_flag(str[i++]);
		if (i < n && str[n] == '.')
			flags += char_to_flag(str[i++]);
	}
	if (!ft_strchr(g_conversions, str[i]))
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
	while (begin[n] && ft_strchr(g_flags_num, begin[n]))
		n++;
	if (!ft_strchr(g_conversions, begin[n]))
	{
		return (begin - str + write(1, begin, n));
	}
	return (check_format(begin, n, ap) + (begin - str));
}
