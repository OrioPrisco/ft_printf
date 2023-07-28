/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:38:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 18:10:19 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>
#include <libft.h>

//calculates size of the string that will be created by putnbr_base
//omits the 0x for base 16 conversions
//and the eventual sign
static int	ft_strlen_b(t_ull nb, size_t base_len)
{
	if ((nb / base_len) > 0)
		return (1 + ft_strlen_b(nb / base_len, base_len));
	return (1);
}

//prints a number in a base to standard output
static ssize_t	ft_putnbr_b(t_ull nb, const char *base, size_t base_len, int fd)
{
	if ((nb / base_len) > 0)
		if (ft_putnbr_b(nb / base_len, base, base_len, fd) < 0)
			return (-1);
	return (b_write(fd, &base[nb % base_len], 1));
}

//calculates size of the string the extra stuff :
//the 0x for base 16 conversions
//and the eventual sign
static int	ft_strlen_fluff(t_ull nb,
	int base_len, const t_format *format)
{
	int	size;

	size = 0;
	if (format->sign || (format->flags & (FLAG_PLUS | FLAG_SPACE)))
		++size;
	if (format->precision > 0 || nb != 0)
		if ((format->flags & FLAG_HASH) && base_len == 16 && nb != 0)
			size += 2;
	return (size);
}

//returns the length a number should take
//basically strlen_b with a special case for ) on precision 0
static int	ft_strlen_base(t_ull nb, int base_len, int precision)
{
	if (precision == 0 && nb == 0)
		return (0);
	return (ft_strlen_b(nb, base_len));
}

//number is a long, this way it can hold both int and uints
//base has to be a valid base, no checking is done
//base 16 need to have the 0x/0X after the first \0
//hacky but eh
//to print unsigned make sure to unset the + flag
ssize_t	ft_printfnum(const t_format *format,
	t_ull number, const char *base)
{
	ssize_t	digits;
	int		base_len;
	int		prec;
	int		width;

	base_len = ft_strlen(base);
	digits = ft_strlen_base(number, base_len, format->precision);
	prec = ft_maxint(format->precision, digits);
	width = prec + ft_strlen_fluff(number, base_len, format);
	if ((!(format->flags & (FLAG_MINUS | FLAG_ZERO)) && format->width > width
			&& ft_pad(format->fd, ' ', format->width - width) < 0)
		|| ((format->sign || (format->flags & (FLAG_PLUS | FLAG_SPACE)))
			&& b_write(format->fd, &" +--"[format->sign * 2
					+ (!!(format->flags & FLAG_PLUS))], 1) < 0)
		|| (number && base_len == 16 && format->flags & FLAG_HASH
			&& b_write(format->fd, &base[17], 2) < 0)
		|| ((format->flags & FLAG_ZERO && format->width > width)
			&& ft_pad(format->fd, '0', format->width - width) < 0)
		|| (prec > digits && ft_pad(format->fd, '0', prec - digits) < 0)
		|| (!(format->precision == 0 && number == 0)
			&& (ft_putnbr_b(number, base, base_len, format->fd) < 0))
		|| (format->flags & FLAG_MINUS && format->width > width
			&& ft_pad(format->fd, ' ', format->width - width) < 0))
		return (-1);
	return (ft_maxint(format->width, width));
}
