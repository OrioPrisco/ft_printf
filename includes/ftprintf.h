/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:58:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2022/11/15 16:05:40 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <sys/types.h>
# include <stdarg.h>

typedef enum e_flags
{
	FLAG_NONE			= 0,
	FLAG_ZERO			= 1 << 0,
	FLAG_SPACE			= 1 << 1,
	FLAG_HASH			= 1 << 2,
	FLAG_PLUS			= 1 << 3,
	FLAG_MINUS			= 1 << 4,
	FLAG_FIELD_WIDTH	= 1 << 5,
	FLAG_PRECISION		= 1 << 6,
}	t_flags;

int		ftprintf(char *s, ...);
ssize_t	ft_pad(char c, ssize_t repeat);
int		find_parseable(char *str, va_list *ap);
ssize_t	ft_printfchar(t_flags flags, int precision, int width, va_list *ap);
ssize_t	ft_printfstr(t_flags flags, int precision, int width, va_list *ap);
ssize_t	ft_printfptr(t_flags flags, int precision, int width, va_list *ap);
ssize_t	ft_printfint(t_flags flags, int precision, int width, va_list *ap);
ssize_t	ft_printfuint(t_flags flags, int precision, int width, va_list *ap);
ssize_t	ft_printfhex(t_flags flags, int precision, int width, va_list *ap);
#endif
