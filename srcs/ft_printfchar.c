/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:25 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/17 18:35:03 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>
#include <libft.h>
#include <unistd.h>

ssize_t	ft_printfchar(t_flags flags, int precision, int width, va_list *ap)
{
	char	c;

	c = (char)va_arg(*ap, int);
	(void)precision;
	if (width > 1 && !(flags & FLAG_MINUS))
		if (ft_pad(' ', width - 1) < 0)
			return (-1);
	if (write(1, &c, 1) < 0)
		return (-1);
	if (width > 1 && (flags & FLAG_MINUS))
		if (ft_pad(' ', width - 1) < 0)
			return (-1);
	if (width > 1)
		return (width);
	return (1);
}
