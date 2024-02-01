/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/01 17:11:46 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int Executor(t_data *data)
{
	// printf("nopipes:%d\n", data->numb_of_pipes);
	int	i;

	i = -1;
	while (data->nodes[++i])
		get_fds(data, i);
	if (data->numb_of_pipes == 0)
	{
		single_command(data, 0);
	}
	else if (data->numb_of_pipes != 0 && g_exit_status == 0)
		piperino9(data->nodes, data);
	return (0);
}

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword);
	// printf("HAHA,SOFUNNY;%zu\n", ft_strlen(str));
	if (ft_strlen(str) > 0 && (ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

int	cnt_bytes(char **arr)
{
	int	i;
	int	bytes;

	bytes = 0;
	i = -1;
	while (arr[++i])
		bytes += ft_strlen(arr[i]) + 1;
	bytes += (i + 1) * sizeof(char *);
	return (bytes);
}

int	single_command(t_data *data, int i)
{
	// printf("in single_command:%s\n", data->nodes[i]->split_command[0]);
	// printf("in single_command:%s\n", data->nodes[i]->split_command[1]);
// enum for checking alll keywords before... if it doesnt match -> print error
	if (!ft_strcmp("echo", data->nodes[i]->command))
		echo(data->nodes[i]);
	else if (cmp_keyword("pwd",data->nodes[i]->split_command[0]))
	{
		data->nodes[i]->output = getpwd();
		printf("%s\n", data->nodes[i]->output);
	}
	else if (cmp_keyword("cd", data->nodes[i]->split_command[0]))
		cd(data->nodes[i], data);
	else if (cmp_keyword("export", data->nodes[i]->split_command[0]))
	{
		// unset(data->nodes[i]->split_command, &data->envp);
		export(data->nodes[i]->split_command, &data->envp);
	}
	else if (cmp_keyword("unset", data->nodes[i]->split_command[0]))
	{
		unset(data->nodes[i]->split_command, &data->envp);
		// unset(data->nodes[i]->split_command[1], &data->envp);
	}
	else if (cmp_keyword("env", data->nodes[i]->split_command[0]))
		printenv(data->envp);
	else if (cmp_keyword("exit", data->nodes[i]->split_command[0]))
	{
		g_exit_status = 69;
		free_and_close_data(data);
	}
	else
	{
		// printf("(single_command) - exec_cmd\n");
		if (data->nodes[i]->split_command[0])
			exec_cmd(data->nodes[i]->split_command, data);
	}
	return (0);
}

void	exec_cmd(char **split_command, t_data *data)
{
		int status;
		int		pid;
		char    *command;
        char    **path;
        int     i;
        
        path = malloc(sizeof(char *) * 2);
        command = NULL;
		path[0] = ft_strdup("$PATH");
        path[1] = ft_strdup("\0");
        expand_vars(path, 0, data);
        path  = ft_split(path[0], ':');
        i = 0;
        while (path[i])
        {
                if (split_command[0][0] == '/' || (split_command[0][0] == '.' && split_command[0][1] == '/'))
                        {
                                command = ft_strdup(split_command[0]);
								break;
                        }
                command = ft_strjoin(path[i],"/");
                command = ft_strjoin(command, split_command[0]);
                if (access(command,F_OK) == 0)
                        break ;
                i++;
        }
        if (access(command,F_OK) == 0)
        {
                if ((pid = fork()) == -1)
                {
                        g_exit_status = 1;
                        perror("fork error");
                }
                else if (pid == 0 && g_exit_status == 0)
                {
                        // split_command++; <- this made it bugging
                        // printf("cmd1:%s, path1:%s\n", split_command[1], command);
                        // printf("cmd1:%s, path1:%s\n", split_command[2], command);
                        // printf("cmd1:%s, path1:%s\n", split_command[3], command);
                        execve(command, split_command, data->envp);
                        /*free(command);
                        printf("Return not expected. Must be an execve error.\n");
                        g_exit_status = 420;
                        free_and_close_data(data); // this can go after we are done implementing
                        */
                }
                signal(SIGQUIT, SIG_IGN);
                waitpid(pid, &status, 0);
                if (WIFEXITED(status))
                        g_exit_status = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                        g_exit_status = 127 + WIFSIGNALED(status);
        }
        else
        {
                printf("command not found\n");
                g_exit_status = 127;
        }
        if (command)
                free(command);
}
/*
0 		Successful execution 	 
1 		Catch generic errors 	
2 		Improper command usage 	
127 	The issue in path resolution
130 	Fatal error 	When interrupted by Ctrl+C
255 	Out of range 	When the exit code exceeds 255
*/