# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 15:27:59 by OrioPrisc         #+#    #+#              #
#    Updated: 2023/07/28 14:07:07 by OrioPrisc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libftprintf.a
SRC					=	parse.c\
						ft_printfutils.c\
						ft_printfchar.c\
						ft_printfstr.c\
						ft_printfnum.c\
						ft_printfnums.c\
						ft_printfnums2.c\
						ft_printfpercent.c
SRC_FOLDER			=	srcs/
HEADERS_FOLDER		=	includes/\
						../includes/ #path to libft.h

OBJ_FOLDER			=	objs/
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -fPIC

OBJS				=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
COMMANDS			=	$(patsubst %.c,$(OBJ_FOLDER)%.cc,$(SRC))
DEPENDS				:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC))

all: $(NAME) compile_commands.json

-include $(DEPENDS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

COMP_COMMAND = $(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@

CONCAT = awk 'FNR==1 && NR!=1 {print ","}{print}'

$(OBJ_FOLDER)%.o $(OBJ_FOLDER)%.cc: $(SRC_FOLDER)%.c Makefile
	$(COMP_COMMAND)
	@printf '{\n\t"directory" : "$(shell pwd)",\n\t"command" : "$(COMP_COMMAND)",\n\t"file" : "$<"\n}' > $(OBJ_FOLDER)$*.cc

compile_commands.json : $(COMMANDS) Makefile
	@echo "Making compile_commands.json"
	@echo "[" > compile_commands.json
	@$(CONCAT) $(COMMANDS) >> compile_commands.json
	@echo "]" >> compile_commands.json

clean:
	rm -f $(OBJS) $(COMMANDS) $(DEPENDS)

fclean: clean
	rm -f $(NAME) compile_commands.json

re: fclean all

.PHONY: all clean fclean re
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
