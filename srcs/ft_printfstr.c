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
#include <libft.h>
#include <unistd.h>

ssize_t	ft_printfstr(t_flags flags, int precision, int width, va_list *ap)
{
	char	*str;
	ssize_t	len;

	str = va_arg(*ap, char *);
	if (precision >= 0)
		len = ft_strnlen(str, precision);
	else
		len = ft_strlen(str);
	if (!(flags && FLAG_MINUS) && (len < width) && ft_pad(' ', width - len) < 0)
		return (-1);
	if (write(1, str, len) < 0)
		return (-1);
	if (flags && FLAG_MINUS && (len < width) && ft_pad(' ', width - len) < 0)
		return (-1);
	if (len < width)
		return (width);
	return (len);
}
