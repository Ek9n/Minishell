#include "minishell.h"

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword);
	if ((ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	single_command(t_data *data,int i)
{
	// printf("in single_command:%s\n", data->INstruct[i]->word_clean);
	if (cmp_keyword("echo", data->nodes[i]->split_command[0]))
	{
		data->nodes[i]->output = echo(data->nodes[i]->command);
		printf("%s", data->nodes[i]->output);
	}
	else if (cmp_keyword("pwd",data->nodes[i]->split_command[0]))
	{
		data->nodes[i]->output = getpwd();
		printf("%s\n", data->nodes[i]->output);
	}
	else if (cmp_keyword("cd", data->nodes[i]->split_command[0]))
		cd(data->nodes[i]->split_command[1], &data->envp);
	else if (cmp_keyword("export", data->nodes[i]->split_command[0]))
	{
		unset(data->nodes[i]->command, &data->envp);
		export(data->nodes[i]->command, &data->envp);
	}
	else if (cmp_keyword("unset", data->nodes[i]->split_command[0]))
		unset(data->nodes[i]->split_command[1], &data->envp);
	else if (cmp_keyword("env", data->nodes[i]->split_command[0]))
		printenv(data->envp);
	else if (cmp_keyword("exit", data->nodes[i]->split_command[0]))
	{
		g_exit_status = 69;
		free_and_close_data(data);
	}
	else
	{
		printf("(single_command) - exec_cmd\n");
		exec_cmd(data->nodes[i]->split_command, data);

	}
	return (0);
}
// /*
int	piperino9(t_words **nodes,t_data *data)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	*pids;
	int		i;
	int		j;

    pids = malloc((data->numb_of_pipes + 1) * sizeof(int));
    pipe_fd = malloc(data->numb_of_pipes * sizeof(int *));
	i = -1;
	while (++i < data->numb_of_pipes)
	{
		pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(pipe_fd[i]) == -1)
			error_exit("(piperino6) Pipe creation failed\n");
	}
	// printf("PIPES:%d\n", data->numb_of_pipes);
    i = 0;
    while (nodes[i] != NULL)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
			if (data->numb_of_pipes > 0)
			{
				// Handle Pipes
				if (i == 0 && nodes[0]->fd_in != STDIN_FILENO)
					dup2(nodes[0]->fd_in, STDIN_FILENO);
				if (i != 0)
					dup2(pipe_fd[i - 1][0], STDIN_FILENO);
				if (i < data->numb_of_pipes)
					dup2(pipe_fd[i][1], STDOUT_FILENO);
				// if (i == data->numb_of_pipes && nodes[i]->fd_out != STDOUT_FILENO)
				// 	dup2(nodes[i]->fd_out, STDOUT_FILENO);

				// // Closing Pipearray:
				j = 0;
				while (j < data->numb_of_pipes)
				{
					close(pipe_fd[j][0]);
					close(pipe_fd[j][1]);	
					j++;		
				}
			}
            // Execve:
			single_command(data, i);
			exit(0); // here may we need some function to exit correct
        }
		if (i != 0)
		{
			close(pipe_fd[i - 1][0]);
			close(pipe_fd[i - 1][1]);
		}
		i++;
		//free_piperino2(INstruct[i], cmd1, path1);
    }
    for (int j = 0; j < i; j++)
    {
        if (j < data->numb_of_pipes)
        {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
        }
    }
    for (int j = 0; j < i; j++)
    {
        waitpid(pids[j], NULL, 0);
    }
    return (i);
}
// */
int Executor(t_data *data)
{
	int	i;
	int redir;

	redir = 0;
	i = 0;
	if (g_exit_status == 0)
		piperino9(data->nodes, data);
	return (i);
}
