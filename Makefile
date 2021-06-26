# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/26 20:43:42 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c
CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
LDLIBS		= -L ./libft/ -lft
LFT         = libft/libft.a
NAME		= push_swap


all:		$(NAME)

$(NAME):	$(LFT)
			$(CC) $(CFLAGS) $(DFLAGS) $(LDLIBS) $(SRCS) -o $(NAME)

$(LFT):
			$(MAKE) -C ./libft/

clean:		
			$(MAKE) -C ./libft/ clean

fclean:		clean
			$(MAKE) -C ./libft/ fclean
			$(RM) $(NAME)
			$(RM) -r *.dSYM

re:			fclean all

bonus:
			$(CC) $(CFLAGS) $(DFLAGS) $(BNS_SRCS) -o $(NAME)

.PHONY:		all clean fclean re bonus
