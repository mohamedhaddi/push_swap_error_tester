# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/23 23:52:30 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
NAME		= push_swap

all:		$(NAME)

$(NAME):	
			$(CC) $(CFLAGS) $(DFLAGS) $(SRCS) -o $(NAME)

clean:		
			$(RM) -r *.dSYM

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:
			$(CC) $(CFLAGS) $(DFLAGS) $(BNS_SRCS) -o $(NAME)

.PHONY:		all clean fclean re bonus
