/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/20 09:56:07 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword);
	if ((ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
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

void	exec_cmd(char **split_command,t_data *data)
{

	int pid;
	int status;
	char	*command;

	if (ft_strnstr(split_command[0], "/bin/", 5) != NULL)
		command = ft_strdup(split_command[0]);
	else
		command = ft_strjoin("/bin/",split_command[0]);
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
			// printf("cmd1:%s, path1:%s\n", split_command[0], command);
			execve(command, split_command, data->envp);
			/*free(command);
			printf("Return not expected. Must be an execve error.\n");
			g_exit_status = 420;
			free_and_close_data(data); // this can go after we are done implementing
			*/
		}
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