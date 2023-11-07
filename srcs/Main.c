/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/07 14:07:26 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**arrdup(char **enviroment)
{
	int		rows;
	int		i;
	char	**dup;

	rows = 0;
	while (enviroment[rows])
		rows++;
	i = 0;
	dup = ft_calloc(rows + 2, sizeof(char **));
	if (!dup)
		return (NULL);
	rows = 0;
	while (enviroment[rows] != NULL)
	{
		dup[rows] = ft_strdup(enviroment[rows]);
		if (dup[rows] == NULL)
			return (NULL);
		rows++;
	}
	dup[rows] = NULL;
	return (dup);
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
		printf("slash");
	fflush(0);
}	

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	t_words				**words;
	char				*input;
	int					b;

	(void)argc;
	(void)argv; // We should duplicate argc argv and envp to our struct,
	b = 0;
	words = NULL;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	while (true)
	{
		input = readline("Minishell>>: ");
		if (input)
			add_history(input); // history works
		words = init_word_stack(input, words,envp);
		
		parser(words); // maybe just having one copy and passing that to functions as arguments is better, idk. 
	}
	while (words[b] != NULL)
	{
		printf("word: %s at index: %d\n", words[b]->word, b);
		printf("Token: %s at index %d\n", words[b]->token_after_word, b);
		b++;
	}
}
