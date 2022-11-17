/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:42:25 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/17 18:35:35 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdarg.h>
#include <libfth.h>

int	ft_printfstr(t_flags flags, int precision, int width, va_list *ap)
{
	char	*str;
	size_t	len;

	str = va_arg(*ap, char *);
	if (precision >= 0)
		len = ft_strnlen(str, precision);
	else
		len = strlen(str);
	(void)flags;
	return (0);
}
