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

const static char	*g_flags = ".0 #+-";
const static char	*g_flags_num = ". #+-0123456789";
const static char	*g_conversions = "cspdiuxX%";

void	find_parseable(char *str)
{
	size_t	n;
	char	*begin;

	begin = strchrnul(str, '%');
	write(1, str, begin - str);
	if (!*begin)
		returni ;
	n = 1;
	while (begin[n] && ft_strchr(begin[n], g_flags_num))
		n++;
	if (!ft_strchr(begin[n], g_conversions))
		return ; //BAD FORMAT
	parse(begin, n);
}

// any of flags (no .) [[any number]+.[any number]+]any of flags(no .)
void	parse(char *str, size_t n)
{
}
