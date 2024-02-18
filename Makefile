# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2024/02/18 21:27:06 by jfoltan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Minishell
CFLAGS			=	-g -Wall -Wextra -Werror
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

SRCS =	Main.c					\
		lexer_1.c				\
		lexer_2.c				\
		lexer_3.c				\
		lexer_utils_1.c			\
		lexer_utils_2.c			\
		enviromentvars_1.c		\
		enviromentvars_2.c		\
		utils_1.c				\
		redirections.c			\
		redirections_utils_1.c 	\
		redirections_utils_2.c 	\
		piperino_1.c			\
		piperino_2.c			\
		builtins_1.c			\
		builtins_2.c			\
		expander_1.c			\
		expander_2.c			\
		executor.c				\
		executor_utils_1.c		\
		executor_utils_2.c		\
		executor_utils_3.c		\
		Error.c					\
		signals.c				\
		error_checks.c			\

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
