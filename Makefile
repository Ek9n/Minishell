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

NAME			=	Minishell
CFLAGS			=	-g #-Wall -Wextra -Werror
LDFLAGS			=	-lreadline -lhistory
RM				=	rm -rf
LIBFT_FOLDER	=	./libft/
LIBFT			=	$(LIBFT_FOLDER)libft.a
SAVEF_FOLDER	=	./ft_savef/
SAVEF			=	$(SAVEF_FOLDER)ft_savef.a
SRC_FOLDER		=	./srcs/
INC_FOLDER		=	./includes/
HEADERS			=	-I $(INC_FOLDER)
VPATH			=	$(SRC_FOLDER)

SRCS =	Main.c \
		Error.c \
		parser_utils_1.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(SAVEF) $(NAME)

$(LIBFT):
	make -C $(LIBFT_FOLDER)

$(SAVEF):
	make -C $(SAVEF_FOLDER)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(HEADERS) -o $(NAME) $(LIBFT) $(SAVEF) $(LDFLAGS)

clean:
	make clean -C $(LIBFT_FOLDER)
	make clean -C $(SAVEF_FOLDER)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(SAVEF)

re: fclean all

.PHONY: all clean fclean re
