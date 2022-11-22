/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfpercent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:12:04 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/22 11:26:18 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftprintf.h>
#include <unistd.h>

ssize_t	ft_printfpercent(t_flags f, int p, int w, va_list *a)
{
	(void)f;
	(void)p;
	(void)w;
	(void)a;
	if (write(1, "%", 1) < 0)
		return (-1);
	return (1);
}
