/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/10 12:55:06 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "../libft/libft.h"
# include "../ft_savef/ft_savef.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>

extern int g_exit_status;

typedef struct redirection
{
	char  	*whole_command;
	char  	**split_command;
	int		fd_out;
	int		fd_in;
} 	t_redirection;

typedef struct s_words
{
	char	*word; //julius Lexer
	char	*word_clean; //Hannes Parser
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	t_redirection	*redirection;
}	t_words;

typedef struct s_data
{
	char	**envp;
	int	    original_fd_in;
	int	    original_fd_out;
	t_words	**INstruct;
}	t_data;

enum	errors {
	ALLOCERR,
	SYNERR,		
};

// MAIN_UTILS
void	puterr(int err);
int		ft_strcmp(const char *s1, const char *s2);
char *ft_join(char **arr);
void free_and_close_data(t_data *data);
// SIGNALS
void	sig_handler_c(int sig);
void	assign_signals(void);
void  assign_interactive_backslash(int sig);
void assign_interactive_C(int sig);
void assign_empty_line(int sig);
void  assign_interactive_signals(void);

// ENVIROMENT
char	**arrdup(char **enviroment);
int		cntenv(char **env);
void	freeenv(char **env);
void	delete_env_var(char *name, char ***env);
void	add_env_var(char *name, char ***env);
int		find_char_from_index(char *str, char c, int index);
char	*expand_env(char *str, char **env);
char 	*dollar_baby(char *str);
// BUILTINS
void	printenv(char **env);
void	unset(char *str, char ***env);
void	export(char *str, char ***env);
char	*echo(char *word);
int		cd(char *dir, char ***env);
int		ls(char *dir);
char	*getpwd(void);
		//make exit
// REDIRECTIONS
void	init_redirection(t_words **words, int i);
int		check_for_redirection(t_words **words);
void 	get_fds(t_data *data,int index);

// LEXER 
void	clean_word(t_words *INstruct);
int		is_in_quotes(char * line);
int		check_token_syntax(char *str);
char	*trimstr(char *str,int i);
char	*tokenizer(char **line,t_data *data);
t_words	**init_word_stack(char *line, t_words **words,t_data *data);
void	clean_words(t_words **INstruct);
void free_dirty_words(t_words **words);
// PARSER


// EXECUTOR 
<<<<<<< HEAD
void	execute_single_command(char *clean_word,t_data *data);
=======
void	exec_cmd(char *clean_word,t_data *data);
>>>>>>> WORKS03
int		Executor(t_data *data);
//DEBUG 
void 	print_words(t_words **words);

//utils_1.c
void	redirection_space_extender(char **dirty_word);

<<<<<<< HEAD

=======
>>>>>>> WORKS03
#endif