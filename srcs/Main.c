/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/01/21 12:48:01 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	data->envp_pipe[0] = -1;
	data->envp_pipe[1] = -1;
	data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
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
		if (input[0] != '\0')
			add_history(input);
		if (input && input[0] != '\0')
		{
			assign_interactive_signals();
			data->nodes = init_nodes(input, data);
			get_fds(data,0); //move this to init_nodes
			// print_nodes(data->nodes);
			if (data->nodes != NULL)
				Executor(data);
		}
			// free_and_close_data(data);
		printf("After routine. (in main)\n");
		// fflush(0);		
	}
}

/* TODO
echo < file1 "how are you" echo doesnt actually read standard in, it reads argument. does our work like that ? 
exit codes redo them 
only tabs dont get interpreted as command, fix
clean quotes from input eg. echo "hello" "world" -> echo hello world
exit doesnt exit lol, also, arguments ? 
echo $? doesnt work (expr $? +$?)
echo "cat lol.c | cat > lol.c" empty
echo '$USER' = '|USER'
export doesnt work
unset doesnt work
cd doesnt work
after check unset path and command execution
relative path ?

Minishell>>: echo blabla sadad #asdda 'sad 'a"sd'
	blabla sadad #asdda sad asd'
*/