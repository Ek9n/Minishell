# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2024/01/07 13:02:50 by jfoltan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Minishell
CFLAGS			=	-g# -Wall -Wextra -Werror
LDFLAGS			=	-lreadline -lhistory
RM				=	rm -rf
LIBFT_FOLDER	=	./libft/
LIBFT			=	$(LIBFT_FOLDER)libft.a
SAVEF_FOLDER	=	./ft_savef/
SAVEF			=	$(SAVEF_FOLDER)ft_savef.a
SRC_FOLDER		=	./srcs/
INC_FOLDER		=	./includes/
OBJ_FOLDER		=	./objs/
HEADERS			=	-I $(INC_FOLDER)
VPATH			=	$(SRC_FOLDER)

SRCS =	Main.c				\
		Error.c				\
		utils_1.c			\
		lexer.c				\
		Parser.c			\
		parser_utils_1.c	\
		executor.c			\
		enviromentvars.c	\
		redirections.c		\
		signals.c

OBJS = $(patsubst %.c, $(OBJ_FOLDER)/%.o, $(notdir $(SRCS)))

all: $(LIBFT) $(SAVEF) $(NAME)

$(LIBFT):
	make -C $(LIBFT_FOLDER)

$(SAVEF):
	make -C $(SAVEF_FOLDER)

$(OBJ_FOLDER)/%.o: %.c
	mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(HEADERS) -o $(NAME) $(LIBFT) $(SAVEF) $(LDFLAGS)

clean:
	make clean -C $(LIBFT_FOLDER)
	make clean -C $(SAVEF_FOLDER)
	$(RM) $(OBJ_FOLDER)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(SAVEF)

re: fclean all

.PHONY: all clean fclean re
