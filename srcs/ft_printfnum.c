/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:38:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/19 15:24:32 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>
#include <unistd.h>
#include <libft.h>

//calculates size of the string that will be created by putnbr_base
//includes the 0x for base 16 conversions
//and the eventual sign
static int	ft_strlen_b(unsigned long nb, const char *base, size_t base_len)
{
	if ((nb / base_len) > 0)
		return (1 + ft_strlen_b(nb / base_len, base, base_len));
	return (1);
}

//prints a number in a base to standard output
static ssize_t	ft_putnbr_b(long nb, const char *base, size_t base_len)
{
	if ((nb / base_len) > 0)
		if (ft_putnbr_b(nb / base_len, base, base_len) < 0)
			return (-1);
	return (write(1, &base[nb % base_len], 1));
}

static int	ft_strlen_base(long nb, const char *base, int pws[3], t_flags flags)
{
	int	size;
	int	base_len;

	base_len = ft_strlen(base);
	size = 0;
	if (pws[2] || (flags & (FLAG_PLUS | FLAG_SPACE)))
		++size;
	if (pws[0] > 0 || nb != 0)
	{
		if (base_len == 16 && (flags & FLAG_HASH))
			size += 2;
		return (size + ft_strlen_b(nb, base, ft_strlen(base)));
	}
	return (size);
}

//number is a long, this way it can hold both int and uints
//base has to be a valid base, no checking is done
//base 16 need to have the 0x/0X after the first \0
//hacky but eh
//to print unsigned make sure to unset the + flag
ssize_t	ft_printfnum(t_flags flags,
		int pws[3], unsigned long number, const char *base)
{
	ssize_t	length;
	int		base_len;
	int		precision;

	base_len = ft_strlen(base);
	length = ft_strlen_base(number, base, pws, flags);
	precision = FT_MAX(pws[0], length);
	if ((!(flags & (FLAG_MINUS | FLAG_ZERO)) && pws[1] > precision
			&& ft_pad(' ', pws[1] - precision) < 0)
		|| ((pws[2] || (flags & (FLAG_PLUS | FLAG_SPACE)))
			&& write(1, &" +--"[pws[2] * 2 + ((flags & FLAG_PLUS) > 0)], 1) < 0)
		|| (!(pws[0] == 0 && number == 0) && base_len == 16 && flags & FLAG_HASH
			&& write(1, &base[17], 2) < 0)
		|| ((flags & FLAG_ZERO && pws[1] > precision)//
			&& ft_pad('0', pws[1] - precision) < 0)//
		|| (precision > length
			&& ft_pad('0', precision - length) < 0)
		|| (!(pws[0] == 0 && number == 0)
			&& (ft_putnbr_b(number, base, base_len) < 0))
		|| (flags & FLAG_MINUS && pws[1] > precision
			&& ft_pad(' ', pws[1] - precision) < 0))
		return (-1);
	if (pws[1] > length)
		return (pws[1]);
	return (length);
}
