/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/15 15:33:17 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "../ft_savef/ft_savef.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_exit_status;

typedef struct s_words
{
	char	*command;
	char	**split_command;
	int		num_of_elements;
	int		fd_out;
	int		fd_in;
	char	*output;
}			t_words;

typedef struct s_data
{
	char	**envp;
	int		original_fd_in;
	int		original_fd_out;
	int		numb_of_pipes;
	int		last_exit_status;
	t_words	**nodes;
}			t_data;

enum		e_errors
{
	ALLOCERR,
	SYNERR,
};

// MAIN_UTILS
void		puterr(int err);
int			ft_strcmp(const char *s1, const char *s2);

char		*ft_join(char **arr);
void		free_and_close_data(t_data *data);

// SIGNALS
void		sig_handler_c(int sig);
void		assign_signals(void);
void		assign_interactive_backslash(int sig);
void		assign_interactive_c(int sig);
void		assign_empty_line(int sig);
void		assign_interactive_signals(void);
// ENVIROMENT
char		**arrdup(char **enviroment);
int			cntenv(char **env);
void		freeenv(char **env);
void		delete_env_var(char *name, char ***env);
void		add_env_var(char *name, char ***env);
int			find_char_from_index(char *str, char c, int index);
char		*dollar_baby(char *str);
void		printenv(char **env);
// BUILTINS
// builtins_1.c
int		echo(t_words *node);
int		cd(t_words *node, t_data *data);
int		ls(char *dir);
// builtins_2.c
void	unset(char **split_cmds, char ***env);
void	export(char **split_cmds, char ***env);
int		ft_strxcmp(const char *s1, const char *s2, size_t n);
int		cmp_keywordx(char *keyword, char *str);
char	*getpwd(void);

// builtin_utils
int			correct_input(char **cmds);
void		purge_arr(char *cmds, char ***env);

// REDIRECTIONS
void		get_fds(t_data *data, int index);
void		handle_open_fail(t_data *data,int i);
void		cleanup(t_data *data, int i, int a, int begin);
void		handle_heredoc(t_data *data, int i);
void		do_output_truncate(t_data *data, int i, int a, int *begin);
void		do_output_append(t_data *data, int i, int a, int *begin);
void		do_input(t_data *data, int i, int a, int *begin);
void		do_heredoc(t_data *data, int i, int a, int *begin);
int			check_token_syntax(char *str);
int			ft_heredoc(char *delimiter, t_data *data);
int			is_in_quotes(char *string);
void		init_vars(int *counter, int *a, int *begin);

// LEXER
int			skip_spaces(char *str);
void		detect_quote(char *dirty_word, bool *quotes, int *last_quote);
int			redir_case(char *c);
char		*comb_extd_word(char **extd_words);
int			get_num_of_pipes(char *str);

// lexer_1.c
void		redirection_space_extender(char **dirty_word);
void		clean_spaces_in_command(char **command);
// lexer_2.c
void		replace_spaces_and_pipes_in_quotes(char *input);
void		putback_spaces_and_pipes_in_quotes(char **input, t_data *data);
// lexer_3.c
void		remove_quotes(char **word);
t_words		**init_nodes(char *input, t_data *data);

// ERROR CHECKS
int			valid_input(char *str);
int			quote_error(char *str);

// expander
int			find_var(char *str, char **envp);
char		*put_var(char **str, int dollar_pos, char **envp);
int			expand_vars(char **input, int i, t_data *data);

// PARSER
int			single_command(t_data *data, int i);
int			piperino9(t_words **nodes, t_data *data);

// EXECUTOR
int			single_command(t_data *data, int i);
int			check_for_only_tab_or_space(char *str);
void		exec_cmd(char **split_command, t_data *data);
int			executor(t_data *data);
int			cmp_keyword(char *keyword, char *str);
int			check_for_only_tab_or_space(char *str);
int			count_spaces(char *str);
int			count_commands(char **split_command);
void		copy_commands(char **new_split, char **temp_split_one,
				char **old_split);
void		handle_access(char *command);
void		handle_fork_error(void);
void		handle_exit_status(int status);
char		*find_path(char **split_command, char **path, t_data *data);
char		*join_path_and_command(char *path, char *split_command);
char		*get_command(char **split_command);
void		handle_fork_error(void);
void		handle_access(char *command);

// DEBUG
void		print_nodes(t_words **nodes);

// utils_1.c
// void	redirection_space_extender(char **dirty_word);

// Piperino
// piperino_1.c
void		error_exit(char *msg);
static void	free_peperino(int **pipe_fd, pid_t *pids, int numb_of_pipes);
void		close_pipes(int **pipe_fd, int numb_of_pipes);
void		close_prepipes(int *ij, int **pipe_fd);
void free_arr(char **arr);
// piperino_2.c

void		init_piperino(t_data *data, int ***pipe_fd, pid_t **pids);
void		terminate_piperino(int *ij, int **pipe_fd, pid_t *pids,
				t_data *data);
void		handle_cases(int *ij, int **pipe_fd, t_data *data);
int			piperino9(t_words **nodes, t_data *data);



#endif
