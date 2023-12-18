/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/18 13:07:46 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	t_data				*data;
	char				*input;
	int					b;

	(void)argc;
	(void)argv;
	b = 0;
	data = init_data(data, envp); // Allocate memory for data
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
		data->INstruct = init_word_stack(input, data->INstruct);
		if (data->INstruct != NULL)
			routine(data);
		// printf("After routine (in main)!\n");
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
