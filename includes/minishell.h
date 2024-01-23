/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/23 18:07:37 by jfoltan          ###   ########.fr       */
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

typedef struct s_words
{
	char	*command; //Hannes Parser
	char	**split_command; //julius Lexer
	int		num_of_elements; //julius Lexer
	int		fd_out;
	int		fd_in;
	//int		quotes_case;
	char 	*output; // Hannes Parser
}	t_words;

typedef struct s_data
{
	char	**envp;
	int		envp_pipe[2];
	int	    original_fd_in;
	int	    original_fd_out;
	int	    numb_of_pipes;
	int		last_exit_status;
	t_words	**nodes;
}	t_data;

enum	errors {
	ALLOCERR,
	SYNERR,		
};

// MAIN_UTILS
void	puterr(int err);
int		ft_strcmp(const char *s1, const char *s2);
char 	*ft_join(char **arr);
void 	free_and_close_data(t_data *data);

// SIGNALS
void	sig_handler_c(int sig);
void	assign_signals(void);
void  	assign_interactive_backslash(int sig);
void 	assign_interactive_C(int sig);
void 	assign_empty_line(int sig);
void 	assign_interactive_signals(void);
// ENVIROMENT
char	**arrdup(char **enviroment);
int		cntenv(char **env);
void	freeenv(char **env);
void	delete_env_var(char *name, char ***env);
void	add_env_var(char *name, char ***env);
int		find_char_from_index(char *str, char c, int index);
char 	*dollar_baby(char *str);
// BUILTINS
void	printenv(char **env);
void	unset(char *str, char ***env);
// void	export(char *str, char ***env);
void	export(char **cmds, char ***env);
char	*echo(char *word);
// int		cd(char *dir, char ***env);
int		ls(char *dir);
char	*getpwd(void);
		//make exit
// builtin_utils
int		correct_input(char **cmds);
void	purge_arr(char *cmds,char ***env);

// REDIRECTIONS
void 	get_fds(t_data *data,int index);

// LEXER 
void 	putback_spaces_and_pipes_in_quotes(char *input);
void	clean_spaces_in_command(char **command);
int		skip_spaces(char *str);
void	redirection_space_extender(char **dirty_word);
void	detect_quote(char *dirty_word, bool *quotes, int *last_quote);
int		redir_case(char *c);
char	*comb_extd_word(char **extd_words);
void 	replace_spaces_and_pipes_in_quotes(char *input);
int 	get_num_of_pipes(char * str);
t_words	**init_nodes(char *input,t_data *data);

// expander
int		find_char_from_index(char *str, char c, int index);
char	*dollar_baby(char *str);
int		find_var(char *str, char **envp);
int		ft_strllen(char *str,int i);
char	*expand_env(char *str, t_data *data);

// PARSER
int		single_command(t_data *data,int i);
int		piperino9(t_words **nodes,t_data *data);

// EXECUTOR 
void	exec_cmd(char **split_command,t_data *data);
int		Executor(t_data *data);

// DEBUG 
void 	print_nodes(t_words **nodes);

//utils_1.c
// void	redirection_space_extender(char **dirty_word);

#endif
