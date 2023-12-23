/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/20 13:59:25 by jfoltan          ###   ########.fr       */
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

	(void)argc;
	(void)argv; 
	data = init_data(data, envp); 
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	while (true)
	{
		input = readline("Minishell>>: ");
		if (input)
		{
			add_history(input); // history works
			data->INstruct = init_word_stack(input, data->INstruct);
		}
		if (data->INstruct != NULL)
			Executor2(data);
		
		printf("After routine (in main)!\n");
	}
}
// for builtins make a function to trigger executor, if command matches
//a builtin, execute that one.
