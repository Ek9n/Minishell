# include "../includes/minishell.h"
int g_exit_status = 0;

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
			data->nodes  = init_nodes(input,data);
			get_fds(data,0); //move this to init_nodes
			// print_nodes(data->nodes);
			if (data->nodes != NULL)
				Executor(data);
		}
			free_and_close_data(data);
		printf("After routine. (in main)\n");
		// fflush(0);		
	}
}
/* TODO
echo < file1 "how are you" echo doesnt actually read standard in, it reads argument. does our work like that ? 
exit codes redo them 
echo $? doesnt work
empty input after command segfaults, because nodes are still initialized
*/