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
static int	ft_strlen_b(long nb, const char *base, size_t base_len)
{
	int	sign;

	sign = 1;
	if (nb < 0)
		sign = -1;
	if ((nb / (base_len * sign)) > 0)
		return (1 + ft_strlen_b(nb / base_len, base, base_len));
	return (1);
}

//prints a number in a base to standard output
static ssize_t	ft_putnbr_b(long nb, const char *base, size_t base_len)
{
	int	sign;

	sign = 1;
	if (nb < 0)
		sign = -1;
	if ((nb / (base_len * sign)) > 0)
		if (ft_putnbr_b(nb / base_len, base, base_len) < 0)
			return (-1);
	return (write(1, &base[(nb % base_len) * sign], 1));
}

static int	ft_strlen_base(long nb, const char *base, int prec, t_flags flags)
{
	int	size;
	int	base_len;

	base_len = ft_strlen(base);
	size = 0;
	if (nb < 0 || (flags & (FLAG_PLUS | FLAG_SPACE)))
		++size;
	if (prec > 0 || nb != 0)
	{
		if (base_len == 16 && (flags & FLAG_HASH))
			size += 2;
		return (ft_strlen_b(nb, base, ft_strlen(base)));
	}
	return (size);
}

/*
static ssize_t	ft_putnbr_base(long nb, const char *base, t_flags flg, int prc)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (nb < 0 || (flg & (FLAG_PLUS | FLAG_SPACE)))
		if (write(1, &" +--"[(nb < 0) * 2 + (flg & FLAG_PLUS)], 1) < 0)
			return (-1);
	if (prc == 0 && nb == 0)
	{
		if (base_len == 16 && (flg & FLAG_HASH))
			if (write(1, &base[17], 2) < 0)
				return (-1);
		return (ft_putnbr_b(nb, base, base_len));
	}
	return (nb < 0 || (flg & (FLAG_PLUS | FLAG_SPACE)));
}
*/
//num is a long, this way it can hold both int and uints
//bas has to be a valid base, no checking is done
//base 16 need to have the 0x/0X after the first \0
//hacky but eh
//to print unsigned make sure to unset the + flag
ssize_t	ft_printfnum(t_flags flg, int pw[2], long num, const char *bas)
{
	ssize_t	len;
	int		base_len;
	int		prec;

	base_len = ft_strlen(bas);
	len = ft_strlen_base(num, bas, pw[1], flg);
	prec = pw[0];
	if (prec < len)
		prec = len;
	if (!(flg & FLAG_MINUS) && pw[1] > prec && ft_pad(' ', pw[1] - prec) < 0)
		return (-1);
	if ((num < 0 || ((flg & (FLAG_PLUS | FLAG_SPACE))
		&& write(1, &" +--"[(num < 0) * 2 + ((flg & FLAG_PLUS) > 0)], 1) < 0))
		|| (pw[0] == 0 && num == 0 && base_len == 16 && flg & FLAG_HASH
		&& write(1, &bas[17], 2) < 0)
		|| (flg & FLAG_ZERO && prec > len && ft_pad('0', prec - len) < 0)
		|| (ft_putnbr_b(num, bas, base_len) < 0)
		|| (flg & FLAG_MINUS && pw[1] > prec && ft_pad(' ', pw[1] - prec) < 0))
		return (-1);
	if (pw[1] > len)
		return (pw[1]);
	return (len);
}
