/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/13 23:32:45 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
	return (data);
}

static void	run(char *input, t_data	*data)
{
	if (input == NULL)
		if (rl_end == 0)
			exit(0);
	if (input && input[0] != '\0')
	{
		add_history(input);
		if (valid_input(input))
		{
			assign_interactive_signals();
			data->nodes = init_nodes(input, data);
			if (data->nodes != NULL)
				executor(data);
		}
		else
			printf("-minishell: %s: Invalid input\n", input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;
	int		a;

	(void)argc;
	(void)argv;
	data = init_data(data, envp);
	while (true)
	{
		assign_signals();
		dup2(data->original_fd_in, 0);
		dup2(data->original_fd_out, 1);
		data->last_exit_status = g_exit_status;
		g_exit_status = 0;
		input = readline("Minishell>>: ");
		run(input, data);
		free (input);
		//free_and_close_data(data);
	}
}

/*
echo bla $USER dodo %PATH

Minishell>>: echo bla "HALLO $USERda $USER" 'hi $USER ad'
bla HALLO @hstein hi $USER ad

Minishell>>: "echo blda > file3"
LEXER1|"echo@blda@>@file3"|
LEXER2|"echo blda > file3"|
blda > file3
*/
