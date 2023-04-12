/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnums2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:38:13 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/12 17:10:30 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>

ssize_t	ft_printfsize_t(t_flags flags, int precision, int width, va_list *ap)
{
	int				pws[3];
	size_t			data;
	const char		*base = "0123456789";

	data = va_arg(*ap, size_t);
	pws[0] = precision;
	pws[1] = width;
	pws[2] = 0;
	flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (flags & FLAG_PRECISION)
		flags &= ~FLAG_ZERO;
	return (ft_printfnum(flags, pws, (unsigned long)data, base));
}
