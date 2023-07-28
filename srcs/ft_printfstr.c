/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:25 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 13:55:30 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>
#include <libft.h>

ssize_t	ft_printfstr(t_format *format, va_list *ap)
{
	char	*str;
	ssize_t	len;

	str = va_arg(*ap, char *);
	if (format->precision >= 0)
		len = ft_strnlen(str, format->precision);
	else
		len = ft_strlen(str);
	if (!(format->flags & FLAG_MINUS) && (len < format->width)
		&& ft_pad(format->fd, ' ', format->width - len) < 0)
		return (-1);
	if (b_write(format->fd, str, len) < 0)
		return (-1);
	if (format->flags & FLAG_MINUS && (len < format->width)
		&& ft_pad(format->fd, ' ', format->width - len) < 0)
		return (-1);
	if (len < format->width)
		return (format->width);
	return (len);
}
