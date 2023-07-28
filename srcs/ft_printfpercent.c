/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfpercent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:12:04 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 13:53:59 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>

ssize_t	ft_printfpercent(t_format *format, va_list *a)
{
	(void)a;
	if (b_write(format->fd, "%", 1) < 0)
		return (-1);
	return (1);
}
