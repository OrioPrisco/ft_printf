/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnums2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:38:13 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 14:19:24 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>

ssize_t	ft_printfsize_t(t_format *format, va_list *ap)
{
	size_t			data;
	const char		*base = "0123456789";

	data = va_arg(*ap, size_t);
	format->sign = 0;
	format->flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format, (unsigned long)data, base));
}
