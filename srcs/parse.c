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

static const char	*g_flags = ".0 #+-";
static const char	*g_flags_num = ". #+-0123456789";
static const char	*g_conversions = "cspdiuxX%";
int	check_format(char *str, size_t n, va_list *ap);
int	parse(char *str, va_list *ap, t_flags flags);

//returns 0 on success
//1 on bad conversion
// for the rest look at heck_format
int	find_parseable(char *str, va_list *ap)
{
	size_t	n;
	char	*begin;

	begin = ft_strchrnul(str, '%');
	write(1, str, begin - str);
	if (!*begin)
		return (0);
	n = 1;
	while (begin[n] && ft_strchr(g_flags_num, begin[n]))
		n++;
	if (!ft_strchr(g_conversions, begin[n]))
		return (1);
	return (check_format(begin, n, ap));
}

t_flags	char_to_flag(char c)
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
	if (c == '.')
		return (FLAG_PRECISION);
	if (ft_isdigit(c))
		return (FLAG_FIELD_WIDTH);
	return (FLAG_NONE);
}

// any of flags (no .) [[any number]+.[any number]+]
//returns
// 0 success
// 2 on bad format string
// this needs to change, has to be bytes written
int	check_format(char *str, size_t n, va_list *ap)
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
	if (!ft_strchr(g_flags, str[i]))
		return (2);
	(void)ap;
	return (0);
}

int	parse(char *str, va_list *ap, t_flags flags)
{
	int		field_width;
	int		precision;
	char	*s;

	field_width = 0;
	precision = 0;
	if (flags & FLAG_FIELD_WIDTH)
	{
		s = ft_strchr(str, '.') - 1;
		while (ft_isdigit(*s))
			s--;
		field_width = ft_atoi(++s);
	}
	if (flags & FLAG_PRECISION)
		precision = ft_atoi(ft_strchr(s, '.') + 1);
	return (0);
}
