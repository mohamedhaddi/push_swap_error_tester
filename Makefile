# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/27 15:59:30 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/main.c
SRCS_BNS	= src_bonus/main_bonus.c
CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
LDLIBS		= -L ./libft/ -lft
LFT         = libft/libft.a
NAME		= push_swap
NAME_BNS	= checker


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
			$(RM) $(NAME_BNS)
			$(RM) -r *.dSYM

re:			fclean all

bonus:		$(LFT)
			$(CC) $(CFLAGS) $(DFLAGS) $(LDLIBS) $(SRCS_BNS) -o $(NAME_BNS)

.PHONY:		all clean fclean re bonus
