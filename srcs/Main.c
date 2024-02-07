/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/07 17:04:00 by hstein           ###   ########.fr       */
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
Different output than bash.. but may not important: // JULIUS
	Minishell>>: cat file3 | wv
	/snap/bin/wv : No such file or directory

only tabs are still interpreted as commands // JULIUS FIXED

Minishell>>: ./home/jfoltan/Desktop/test/a.out 
command not found should be no such file or directory // JULIUS FIXED

debug info in heredoc, maybe add variable expansion? //JULIUS FIXED

cat ctrlc exit code is 131 instead of 130 //JULIUS FIXED

exit with n as argument //JULIUS I guess fixed

----
semi-FIXED for now... removed the last split in getfd for it.. may it makes new problems
	Minishell>>: export baa="env | grep PWD"
		executerEnvVars1:47|
	-minishell: export: '|': not a valid identifier
		executerEnvVars2:49|
----
----------------------------------------------

only spaces provide pwd??? //HANNES FIXED

exho h 			g with tabs //HANNES FIXED

Minishell>>: echo bla | wc < file3
      2       4      22		//HANNES FIXED

Minishell>>: cat < file2 > file3 | wc < file3
0 0 0 						//HANNES FIXED
// Minishell>>: cat f1 > f2 | wc < f2
// 1 1 3
// Minishell>>: echo bla | wc < f3
// 1 1 5
// Minishell>>: cat f1 > f2 | wc < f2
// 1 1 3
// Minishell>>: 
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ cat f1 > f2 | wc < f2
// 1 1 3
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ echo bla | wc < f3
// 1 1 5
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ 
*/
