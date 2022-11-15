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

NAME				= libftprintf.a
SRC					= foo.c
SRC_FOLDER			= srcs/
HEADERS_FOLDER		= includes/;libft/
OBJS				= $(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
OBJ_FOLDER			= objs/
CC					= cc
CFLAGS				= -Wall -Wextra -Werror
LIBFT_PATH			= libft/
LIBFT				= libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
	cp $(LIBFT_PATH)$(LIBFT) $(LIBFT)

$(NAME): $(OBJS) libft.a
	ar rcs $(NAME) $(OBJS)

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c
	$(CC) -c $(CFLAGS) -I$(HEADERS_FOLDER) -L$(LIBFT_PATH) $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
