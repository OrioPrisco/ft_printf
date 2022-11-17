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
#include <unistd.h>

//returns -1 on failure
//or bytes written
ssize_t	ft_pad(char c, size_t repeat)
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
