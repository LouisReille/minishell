# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 14:57:54 by lreille           #+#    #+#              #
#    Updated: 2023/02/19 06:22:27 by lreille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address 
RM = rm -f
LINK = -L$(HOME)/homebrew/opt/readline/lib -lreadline
COMPILE = -I/$(HOME)/homebrew/opt/readlin/include
OBJ = $(SOURCES:.c=.o)

.SILENT:$(OBJ)

SOURCES = sources/ft_split.c\
		sources/exec_binary.c\
	   sources/exec_builtins.c\
	   sources/minishell.c\
	   sources/ft_utils1.c\
	   sources/ft_utils2.c\
	   sources/ft_utils3.c\
	   sources/ft_builtins.c\
	   sources/ft_check.c\
	   sources/ft_smartsplit.c\
	   sources/ft_smartsplit_utils.c\
	   sources/ft_export.c\
	   sources/ft_unset.c\
	   sources/ft_echo_utils1.c\
	   sources/ft_echo_utils2.c\
	   sources/ft_export_utils1.c\
	   sources/ft_export_utils2.c\
	   sources/ft_export_utils3.c\

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LINK) $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) $(COMPILE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
fclean:
	@$(RM) $(NAME) $(OBJ)
re: fclean all

r: all
	@clear && ./minishell

.PHONY: all clean fclean re
