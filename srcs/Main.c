# include "../includes/minishell.h"

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
		a = 0;
		dup2(data->original_fd_in, 0);
		dup2(data->original_fd_out, 1);
		input = readline("Minishell>>: ");
		if (input)
			add_history(input);
		data->nodes  = init_nodes(input,data);
		get_fds(data,0);
		print_nodes(data->nodes);
		if (data->nodes != NULL)
			Executor(data);
		// #bring back the spaces //for now testing.. first split and redirections..

		//unlink(".heredoc");
		// fflush(0);		
	}
}
/* TODO
echo < file1 "how are you" echo doesnt actually read standard in, it reads argument. does our work like that ? 

*/