# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grannou <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 07:41:59 by grannou           #+#    #+#              #
#    Updated: 2021/06/20 09:40:20 by grannou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c \
	ft_printf_utils.c \
	ft_printf_utils2.c \
	ft_printf_utils3.c \
	fill_format.c \
	print_cs.c \
	print_p.c \
	print_di.c \
	print_u.c \
	print_xX.c \
	print_bonus.c \
	print_bonus2.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NORME = norminette *.h && norminette $(SRCS)
RM = rm -rf

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

bonus: $(NAME)

norme:
	$(NORME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus norme clean fclean re
