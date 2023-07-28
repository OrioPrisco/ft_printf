/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:25 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 14:16:32 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>
#include <libft.h>

ssize_t	ft_printfchar(t_format *format, va_list *ap)
{
	char	c;

	c = (char)va_arg(*ap, int);
	if (format->width > 1 && !(format->flags & FLAG_MINUS))
		if (ft_pad(format->fd, ' ', format->width - 1) < 0)
			return (-1);
	if (b_write(format->fd, &c, 1) < 0)
		return (-1);
	if (format->width > 1 && (format->flags & FLAG_MINUS))
		if (ft_pad(format->fd, ' ', format->width - 1) < 0)
			return (-1);
	if (format->width > 1)
		return (format->width);
	return (1);
}
