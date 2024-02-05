/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/06 00:09:00 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;
// int cd_flag = 0;

t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;
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
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (valid_input(input))
			{
				assign_interactive_signals();
				data->nodes = init_nodes(input, data);
	// printf("INITmain:%s\n", data->nodes[0]->command);
				// print_nodes(data->nodes);
				// printf("MAIN:%s\n", data->nodes[0]->split_command[1]);
				if (data->nodes != NULL)
					Executor(data);
			}
			else
				printf("-minishell: %s: Invalid input\n", input);
		}
			 free_and_close_data(data);
		// printf("After routine. (in main)\n");
	}
}

/* TODO
only tabs are still interpreted as commands // JULIUS
FIXED only spaces provide pwd??? //HANNES
exit with n as argument //JULIUS
exho h 			g with tabs //HANNES
cat ctrlc exit code is 131 instead of 130 //JULIUS
----
Minishell>>: export baa="env | grep PWD"
executerEnvVars1:47|
-minishell: export: '|': not a valid identifier
executerEnvVars2:49|
EXIT_ON_FREE: 0 //HANNES
----
Minishell>>: ./home/jfoltan/Desktop/test/a.out 
command not found should be no such file or directory // JULIUS

Minishell>>: cat < file2 > file3 | wc < file3
0 0 0 //HANNES

debug info in heredoc, maybe add variable expansion? //JULIUS

Minishell>>: echo bla | wc < file3
      2       4      22//HANNES
EXIT_ON_FREE: 0 

*/