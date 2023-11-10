/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/10 22:19:05 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
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
	(void)argv; // We should duplicate argc argv and envp to our struct,./Md
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
		// while (words[b] != NULL)
		// {
		// 	printf("word: %s at index: %d\n", words[b]->word, b);
		// 	printf("Token: %s at index: %d\n", words[b]->token_after_word, b);
		// 	b++;
		// }
		routine(words);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	struct sigaction	act;
// 	static t_words **words;
// 	char * input;
// 	int		b;

// 	b = 0;
// 	words = NULL;
// 	sigemptyset(&act.sa_mask);
// 	act.sa_sigaction = &signal_handler;
// 	act.sa_flags = SA_SIGINFO;
// 	sigaction(SIGQUIT, &act, NULL);
// 	sigaction(SIGINT, &act, NULL);
// 	words = malloc(sizeof(t_words*));
// 	words[0] = malloc(sizeof(t_words*));
// 	words[0]->num_of_elements = 1;
// 	while(true)
// 	{
// 		input = readline("Minishell>>: ");
// 		if (input)
// 			add_history(input); // history works
// 		words[0]->word = malloc(1000);
// 		words[0]->word = input;
// 		parser(words);
// 		free(words[0]->word);
// 	}
// }
