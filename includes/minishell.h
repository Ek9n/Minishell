/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/20 16:10:37 by jfoltan          ###   ########.fr       */
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

typedef struct redirection
{
	char  *whole_command;
	int		fd_out;
	int		fd_in;
} 	t_redirection;

typedef struct s_words
{
	char	*word; //julius Lexer
	char	*word_clean; //Hannes Parser
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char crazytoken;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	t_redirection	*redirection;
}	t_words;
typedef struct s_data
{
	char	**envp;
	t_words	**INstruct;
}	t_data;

enum	errors {
	ALLOCERR,
	SYNERR,		
};
// MAIN_UTILS
void	puterr(int err);
int		ft_strcmp(const char *s1, const char *s2);
// ENVIROMENT
char	**arrdup(char **enviroment);
int		cntenv(char **env);
void	freeenv(char **env);
void	delete_env_var(char *name, char ***env);
void	add_env_var(char *name, char ***env);
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
// LEXER 
void	clean_word(t_words *INstruct);
int		is_in_quotes(char * line);
int		check_token_syntax(char *str);
char	*trimstr(char *str,int i);
char	*tokenizer(char **line);
t_words	**init_word_stack(char *line, t_words **words);
void	clean_words(t_words **INstruct);
void free_dirty_words(t_words **words);
// PARSER
int		single_command(t_data *data, int i);
void	routine(t_data	*data);
// EXECUTOR 
void	executor(char *clean_word, char **envp);
int		Executor2(t_data *data);

#endif