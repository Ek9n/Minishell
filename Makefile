# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2023/10/13 14:25:03 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= parser
CFLAGS	= -g #-Wall -Wextra -Werror 
RM		= rm -rf
LIBFT_FOLDER  	= ./libft/
LIBFT  	= $(LIBFT_FOLDER)libft.a
SAVEF_FOLDER  	= ../ft_savef/
SAVEF 	= $(SAVEF_FOLDER)ft_savef.a
HEADERS = -I ./include
SRCS	= 	Main.c \
			Error.c \
			parser_utils_1.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(LIBFT) $(SAVEF)

libft:
	make -C $(LIBFT_FOLDER)

savef:
	make -C $(SAVEF_FOLDER)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(HEADERS) -o $(NAME) $(LIBFT) $(SAVEF)

clean:
	make clean -C $(LIBFT_FOLDER) $(SAVEF_FOLDER)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
