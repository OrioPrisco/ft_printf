/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:36:49 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 13:52:49 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>
#include <stdarg.h>

ssize_t	ft_printfint(t_format *format, va_list *ap)
{
	int				pws[3];
	long			data;
	const char		*base = "0123456789";

	data = va_arg(*ap, int);
	pws[0] = format->precision;
	pws[1] = format->width;
	pws[2] = data < 0;
	if (pws[2])
		data *= -1;
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format->flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfuint(t_format *format, va_list *ap)
{
	int				pws[3];
	unsigned int	data;
	const char		*base = "0123456789";

	data = va_arg(*ap, unsigned int);
	pws[0] = format->precision;
	pws[1] = format->width;
	pws[2] = 0;
	format->flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format->flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfhex(t_format *format, va_list *ap)
{
	int				pws[3];
	unsigned int	data;
	const char		*base = "0123456789abcdef\0000x";

	data = va_arg(*ap, unsigned int);
	pws[0] = format->precision;
	pws[1] = format->width;
	pws[2] = 0;
	format->flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format->flags, pws, data, base));
}

ssize_t	ft_printfhexup(t_format *format, va_list *ap)
{
	int				pws[3];
	unsigned int	data;
	const char		*base = "0123456789ABCDEF\0000X";

	data = va_arg(*ap, unsigned int);
	pws[0] = format->precision;
	pws[1] = format->width;
	pws[2] = 0;
	format->flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format->flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfptr(t_format *format, va_list *ap)
{
	int				pws[3];
	unsigned long	data;
	const char		*base = "0123456789abcdef\0000x";

	format->flags |= FLAG_HASH;
	data = (unsigned long)va_arg(*ap, void *);
	pws[0] = format->precision;
	pws[1] = format->width;
	pws[2] = 0;
	format->flags &= ~(FLAG_SPACE | FLAG_PLUS);
	if (format->flags & FLAG_PRECISION)
		format->flags &= ~FLAG_ZERO;
	return (ft_printfnum(format->flags, pws, data, base));
}
