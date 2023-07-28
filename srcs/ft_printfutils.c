/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:49:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/29 00:49:13 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <libft.h>
#include <unistd.h>

//returns -1 on failure
//or bytes written
ssize_t	ft_pad(int fd, char c, ssize_t repeat)
{
	char		buffer[1024];
	ssize_t		total_bytes;

	total_bytes = repeat;
	while (repeat > 1024)
	{
		if (b_write(fd, ft_memset(buffer, c, 1024), 1024) != 1024)
			return (-1);
		repeat -= 1024;
	}
	if (repeat)
		if (b_write(fd, ft_memset(buffer, c, 1024), repeat) != repeat)
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

static size_t	reset_fullness(size_t *fulness)
{
	size_t	temp;

	temp = *fulness;
	*fulness = 0;
	return (temp);
}

ssize_t	b_write(int fd, const void *mem, size_t n)
{
	static char		buffer[1024];
	static size_t	fullness;

	if (fd < 0)
	{
		return (write(-fd, buffer, reset_fullness(&fullness)));
	}
	if (n >= 1024 - fullness)
	{
		if (write(1, &buffer, reset_fullness(&fullness)) < 0)
			return (-1);
		return (write(fd, mem, n));
	}
	ft_memcpy(buffer + fullness, mem, n);
	fullness += n;
	return (n);
}
