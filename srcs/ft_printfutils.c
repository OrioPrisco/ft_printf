/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:49:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/17 18:36:00 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <libft.h>
#include <unistd.h>

//returns -1 on failure
//or bytes written
ssize_t	ft_pad(char c, ssize_t repeat)
{
	char		buffer[1024];
	ssize_t		total_bytes;

	total_bytes = repeat;
	while (repeat > 1024)
	{
		if (write(1, ft_memset(buffer, c, 1024), 1024) != 1024)
			return (-1);
		repeat -= 1024;
	}
	if (repeat)
		if (write(1, ft_memset(buffer, c, 1024), repeat) != repeat)
			return (-1);
	return (total_bytes);
}

//aside from field width, could do some 1 << g_flags - strchr(g_flags, c)
//simple conversion
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
	if (ft_isdigit(c))
		return (FLAG_FIELD_WIDTH);
	if (c == '.')
		return (FLAG_PRECISION);
	return (FLAG_NONE);
}

ssize_t	advance_str(const char **str, size_t amount)
{
	*str += amount;
	return (amount);
}
