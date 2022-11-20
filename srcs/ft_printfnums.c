/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:36:49 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/19 17:15:37 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>
#include <stdarg.h>

ssize_t	ft_printfint(t_flags flags, int precision, int width, va_list *ap)
{
	int				pws[3];
	long				data;
	const char		*base = "0123456789";

	data = va_arg(*ap, int);
	pws[0] = precision;
	pws[1] = width;
	pws[2] = data < 0;
	if (pws[2])
		data *= -1;
	return (ft_printfnum(flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfuint(t_flags flags, int precision, int width, va_list *ap)
{
	int				pws[3];
	unsigned int	data;
	const char		*base = "0123456789";

	data = va_arg(*ap, unsigned int);
	pws[0] = precision;
	pws[1] = width;
	pws[2] = 0;
	return (ft_printfnum(flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfhex(t_flags flags, int precision, int width, va_list *ap)
{
	int				pws[3];
	unsigned long	data;
	const char		*base = "0123456789abcdef\0000x";

	data = va_arg(*ap, unsigned long);
	pws[0] = precision;
	pws[1] = width;
	pws[2] = 0;
	return (ft_printfnum(flags, pws, data, base));
}

ssize_t	ft_printfhexup(t_flags flags, int precision, int width, va_list *ap)
{
	int				pws[3];
	unsigned long	data;
	const char		*base = "0123456789ABCDEF\0000X";

	data = va_arg(*ap, unsigned long);
	pws[0] = precision;
	pws[1] = width;
	pws[2] = 0;
	flags &= ~(FLAG_SPACE | FLAG_PLUS);
	return (ft_printfnum(flags, pws, (unsigned long)data, base));
}

ssize_t	ft_printfptr(t_flags flags, int precision, int width, va_list *ap)
{
	flags |= FLAG_HASH;
	return (ft_printfhex(flags, precision, width, ap));
}
