/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:58:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/07/28 14:10:16 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <sys/types.h>
# include <stdarg.h>

//. has to be first
# define FLAGS ".0 #+-"
# define FLAGS_NUM ". #+-0123456789"
# define CONVERSIONS "cspdiuxX%U"
# define FLUSH_BUFFER -1

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

typedef unsigned long long	t_ull;

typedef struct s_format {
	t_flags		flags;
	int			precision;
	int			width;
	int			sign;
	int			fd;
	char		conversion;
}	t_format;

// not thread safe
int		ft_printf(const char *s, ...);

//utils
ssize_t	advance_str(const char **str, size_t amount);
t_flags	char_to_flag(char c);

// not thread safe
ssize_t	ft_pad(int fd, char c, ssize_t repeat);
// not thread safe
// if fd is negative, buffer gets flushed
ssize_t	b_write(int fd, const void *mem, size_t n);

//print functions
ssize_t	ft_printfpercent(t_format *format, va_list *ap);
ssize_t	ft_printfchar(t_format *format, va_list *ap);
ssize_t	ft_printfstr(t_format *format, va_list *ap);
ssize_t	ft_printfptr(t_format *format, va_list *ap);
ssize_t	ft_printfint(t_format *format, va_list *ap);
ssize_t	ft_printfuint(t_format *format, va_list *ap);
ssize_t	ft_printfhex(t_format *format, va_list *ap);
ssize_t	ft_printfhexup(t_format *format, va_list *ap);
ssize_t	ft_printfsize_t(t_format *format, va_list *ap);
ssize_t	ft_printfnum(const t_format *format, t_ull n, const char *b);
#endif
