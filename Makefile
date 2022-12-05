# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 15:27:59 by OrioPrisc         #+#    #+#              #
#    Updated: 2022/11/15 15:32:57 by OrioPrisc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libftprintf.a
SRC					=	parse.c\
						ft_printfutils.c\
						ft_printfchar.c\
						ft_printfstr.c\
						ft_printfnum.c\
						ft_printfnums.c\
						ft_printfpercent.c
SRC_FOLDER			=	srcs/
HEADERS_FOLDER		=	includes/\
						../includes/ #path to libft.h
OBJS				=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
OBJ_FOLDER			=	objs/
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c
	$(CC) -c -fPIC $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
