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
						ft_printfchar.c
SRC_FOLDER			=	srcs/
HEADERS_FOLDER		=	includes/\
						libft/
OBJS				=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
OBJ_FOLDER			=	objs/
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
LIBFT_PATH			=	libft/
LIBFT				= 	(LIBFT_PATH)libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS)

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c
	$(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -L$(LIBFT_PATH) $< -o $@ -lft

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
