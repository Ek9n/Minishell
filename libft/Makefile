# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 16:11:14 by sung-hle          #+#    #+#              #
#    Updated: 2023/03/23 17:56:51 by sung-hle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	ft_strchr.c		\
			ft_strrchr.c		\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_strlen.c		\
			ft_memset.c		\
			ft_putchar_fd.c	\
			ft_putstr_fd.c		\
			ft_putnbr_fd.c		\
			ft_substr.c		\
			ft_putendl_fd.c	\
			ft_tolower.c		\
			ft_toupper.c		\
			ft_atoi.c		\
			ft_bzero.c		\
			ft_strdup.c		\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isprint.c		\
			ft_isascii.c		\
			ft_itoa.c 	\
			ft_memchr.c	\
			ft_memcpy.c		\
			ft_memcmp.c		\
			ft_memmove.c	\
			ft_strjoin.c		\
			ft_striteri.c		\
			ft_strmapi.c	\
			ft_strncmp.c	\
			ft_strnstr.c	\
			ft_strtrim.c		\
			ft_split.c		\
			ft_calloc.c	\
			ft_putchar_fd_printf.c	\
			ft_putnbr_base_fd.c	\
			ft_putnbr_fd_printf.c	\
			ft_putnbr_ui_fd_printf.c	\
			ft_putstr_printf_fd.c	\
			ft_printf.c	\
			ft_voidcase.c	\
			ft_lstnew.c \
			ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c	\
			ft_lstdelone.c	\
			ft_lstiter.c	\
			ft_lstlast.c	\
			ft_lstmap.c	\
			ft_lstsize.c \
			ft_gnllcpy.c \
			ft_freebuf.c \
			ft_gnllen.c \
			ft_calloc_gnl.c \
			get_next_line.c
#			ft_error.c
OBJS		= ${SRCS:.c=.o}
NAME		= libft.a
CC			= cc -Wall -Wextra -Werror


all:		${NAME}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

#bonus:		${OBJS} ${OBJS_BONUS}
#			ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

clean:
			rm -f ${OBJS}
#${OBJS_BONUS}

fclean:	clean	
			rm -f ${NAME}

re:			fclean all


.PHONY:		all clean fclean re

