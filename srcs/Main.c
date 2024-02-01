/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/01 17:41:07 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;
int cd_flag = 0;

t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	// data->envp_pipe[0] = -1;
	// data->envp_pipe[1] = -1;
	// data -> original_fd_in = STDIN_FILENO;
	// data -> original_fd_out = STDOUT_FILENO;
	data -> original_fd_in = dup(STDIN_FILENO);
	// data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
	// data -> original_fd_out = dup(STDOUT_FILENO);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;
	int		a;

	(void)argc; //have to protect arguments
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
		if (input == NULL)
			if (rl_end == 0)
				exit(0);
		// if (input[0] != '\0')
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (valid_input(input))
			{
				assign_interactive_signals();
				data->nodes = init_nodes(input, data);
				// print_nodes(data->nodes);
				// printf("MAIN:%s\n", data->nodes[0]->split_command[1]);
				if (data->nodes != NULL)
					Executor(data);
			}
			else
				printf("-minishell: %s: Invalid input\n", input);
		}
			// free_and_close_data(data);
		// printf("After routine. (in main)\n");
		// fflush(0);		
	}
}

/* TODO
exit codes check
cd . 
cd new_mini/ - diuble free
export bii = 15 -> segfault
debug info in HEREDOC
debug info in CD
*/