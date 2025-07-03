# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 17:53:23 by rgu               #+#    #+#              #
#    Updated: 2025/07/03 12:39:40 by rgu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/built_in.c \
		src/built_in2.c \
		src/env_utils.c \
		src/env_utils2.c \
		src/env_utils3.c \
		src/env_utils4.c \
		src/env.c \
		src/env2.c \
		src/execute.c \
		src/execute1.c \
		src/execute2.c \
		src/execute3.c \
		src/execute4.c \
		src/heredoc.c \
		src/main_utils.c \
		src/main_utils2.c \
		src/main.c \
		src/parsing.c \
		src/parsing1.c \
		src/parsing2.c \
		src/path.c \
		src/signals.c \
		src/update_env.c \
		src/utils.c \
		src/utils2.c 
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
.PHONY: all clean fclean re
