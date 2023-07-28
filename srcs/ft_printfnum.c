/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:38:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 13:59:55 by OrioPrisc        ###   ########.fr       */
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
static ssize_t	ft_putnbr_b(t_ull nb, const char *base, size_t base_len)
{
	if ((nb / base_len) > 0)
		if (ft_putnbr_b(nb / base_len, base, base_len) < 0)
			return (-1);
	return (b_write(1, &base[nb % base_len], 1));
}

//calculates size of the string the extra stuff :
//the 0x for base 16 conversions
//and the eventual sign
static int	ft_strlen_fluff(t_ull nb,
	int base_len, int pws[3], t_flags flags)
{
	int	size;

	size = 0;
	if (pws[2] || (flags & (FLAG_PLUS | FLAG_SPACE)))
		++size;
	if (pws[0] > 0 || nb != 0)
		if ((flags & FLAG_HASH) && base_len == 16 && nb != 0)
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
ssize_t	ft_printfnum(t_flags flags,
		int pws[3], t_ull number, const char *base)
{
	ssize_t	digits;
	int		base_len;
	int		precision;
	int		width;

	base_len = ft_strlen(base);
	digits = ft_strlen_base(number, base_len, pws[0]);
	precision = ft_maxint(pws[0], digits);
	width = precision + ft_strlen_fluff(number, base_len, pws, flags);
	if ((!(flags & (FLAG_MINUS | FLAG_ZERO)) && pws[1] > width
			&& ft_pad(1, ' ', pws[1] - width) < 0)
		|| ((pws[2] || (flags & (FLAG_PLUS | FLAG_SPACE)))
			&& b_write(1, &" +--"[pws[2] * 2 + (!!(flags & FLAG_PLUS))], 1) < 0)
		|| (number && base_len == 16 && flags & FLAG_HASH
			&& b_write(1, &base[17], 2) < 0)
		|| ((flags & FLAG_ZERO && pws[1] > width)
			&& ft_pad(1, '0', pws[1] - width) < 0)
		|| (precision > digits
			&& ft_pad(1, '0', precision - digits) < 0)
		|| (!(pws[0] == 0 && number == 0)
			&& (ft_putnbr_b(number, base, base_len) < 0))
		|| (flags & FLAG_MINUS && pws[1] > width
			&& ft_pad(1, ' ', pws[1] - width) < 0))
		return (-1);
	return (ft_maxint(pws[1], width));
}
