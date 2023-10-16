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

CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := ft_savef.a
NAMELFT := libft.a
SOURCES := ft_savef.c ft_savef_utils_A.c ft_savef_utils_B.c
OBJECTS := $(SOURCES:.c=.o)
LIBDIR := ../libft
HEADERS := -I ../libft -I ../includes

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(LIBDIR)
	cp -v $(LIBDIR)/$(NAMELFT) $(NAME)
	ar cr $@ $^

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
