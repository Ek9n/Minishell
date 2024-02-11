/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/11 13:27:37 by jfoltan          ###   ########.fr       */
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
void	export(char **cmds, char ***env);
void	unset(char **split_cmds, char ***env);
// void	unset(char *str, char ***env);
// void	export(char *str, char ***env);
// int		echo(t_words *node);
int		echo(t_words *node);
// int		cd(char *dir, char ***env);
// int		cd(char **split_cmds, char ***env);
int		cd(t_words *node, t_data *data);
int		ls(char *dir);
char	*getpwd(void);
		//make exit
// builtin_utils
int		correct_input(char **cmds);
void	purge_arr(char *cmds,char ***env);

// REDIRECTIONS
void 	get_fds(t_data *data,int index);

// LEXER 
void 	putback_spaces_and_pipes_in_quotes(char **input, t_data *data);
void	clean_spaces_in_command(char **command);
int		skip_spaces(char *str);
void	redirection_space_extender(char **dirty_word);
void	detect_quote(char *dirty_word, bool *quotes, int *last_quote);
int		redir_case(char *c);
char	*comb_extd_word(char **extd_words);
void 	replace_spaces_and_pipes_in_quotes(char *input);
int 	get_num_of_pipes(char * str);
t_words	**init_nodes(char *input,t_data *data);

// ERROR CHECKS
int		valid_input(char *str);
int		quote_error(char *str);

// expander
int find_var(char *str, char **envp);
char *put_var(char **str, int dollar_pos, char **envp);
int	expand_vars(char **input, int i, t_data *data);

// PARSER
int		single_command(t_data *data,int i);
int		piperino9(t_words **nodes,t_data *data);

// EXECUTOR 
void	exec_cmd(char **split_command,t_data *data);
int		executor(t_data *data);
int		cmp_keyword(char *keyword, char *str);
// DEBUG 
void 	print_nodes(t_words **nodes);

//utils_1.c
// void	redirection_space_extender(char **dirty_word);

// Piperino
// piperino_1.c
void	error_exit(char *msg);
void	free_peperino(int **pipe_fd, pid_t *pids, int numb_of_pipes);
void	close_pipes(int	**pipe_fd, int numb_of_pipes);
void	close_prepipes(int *ij, int **pipe_fd);
// piperino_2.c

void	init_piperino(t_data *data, int ***pipe_fd, pid_t **pids);
void	terminate_piperino(int *ij, int **pipe_fd, pid_t *pids, t_data *data);
void	handle_cases(int *ij, int **pipe_fd, t_data *data);
int		piperino9(t_words **nodes, t_data *data);

#endif
