# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 06:46:45 by dkenchur          #+#    #+#              #
#    Updated: 2021/02/12 19:16:30 by dkenchur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

NAME		= libft.a

INCLUDES	= ../includes/

SRCS		= 	ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_strlen.c	\
				ft_tolower.c	\
				ft_toupper.c	\
				ft_strjoin.c	\
				ft_memchr.c	\
				ft_memcmp.c	\
				ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isalnum.c	\
				ft_isascii.c	\
				ft_isprint.c	\
				ft_strlcpy.c	\
				ft_strlcat.c	\
				ft_strdup.c	\
				ft_strchr.c	\
				ft_strrchr.c	\
				ft_strncmp.c	\
				ft_calloc.c	\
				ft_strnstr.c	\
				ft_atoi.c	\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_putnbr_fd.c	\
				ft_substr.c	\
				ft_strtrim.c	\
				ft_strmapi.c	\
				ft_itoa.c	\
				ft_split.c	\
				ft_create_lst.c \
				ft_create_node.c \
				ft_lst_clear.c \
				ft_push_front.c \
				ft_push_back.c

CFLAGS		= -Wall -Wextra -Werror

GREEN		= \033[0;32m

RESET		= \033[0m

OBJS		= $(SRCS:.c=.o)

.c.o:
			@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			@rm -rf $(OBJS)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all
