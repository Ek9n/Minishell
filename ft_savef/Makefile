# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 14:44:34 by hstein            #+#    #+#              #
#    Updated: 2023/02/01 14:44:34 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRCS			= ft_printf.c ft_printf_utils_A.c ft_printf_utils_B.c
# OBJS			= $(SRCS:.c=.o)

# CC				= cc
# CFLAGS			= -Wall -Wextra -Werror
# RM				= rm -f

# NAME			= libftprintf.a

# LIBFT_PATH		= ./libft
# LIBFT			= $(LIBFT_PATH)/libft.a

# all:			$(NAME)

# $(NAME):		$(OBJS)
# 				make -C $(LIBFT_PATH)
# 				ar rcs $(LIBFT) $(OBJS) $(NAME)

# clean:
# 				$(RM) $(OBJS) $(BONUS_OBJS)

# fclean:			clean
# 				$(RM) $(NAME)

# re:				fclean $(NAME)

# .PHONY:			all clean fclean re

CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := ft_savef.a
NAMELFT := libft.a
sources :=  ft_savef.c ft_printf_utils_A.c ft_printf_utils_B.c
objects := $(sources:.c=.o)
LIBDIR := libft
all: $(NAME)
$(NAME): $(objects)
	make -C $(LIBDIR)
	cp -v $(LIBDIR)/$(NAMELFT) $(NAME)
	ar cr $@ $^
# cp -v (verbose = explain what is being dong)
$(objects): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	$(RM) $(objects)
	$(RM) *.o $(LIBDIR)/*.o
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBDIR)/$(NAMELFT)
re: fclean all
.PHONY: all clean fclean re