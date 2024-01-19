/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/19 18:04:14 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			split_command++;
			execve(command, split_command, data->envp);
			/*free(command);
			printf("Return not expected. Must be an execve error.\n");
			g_exit_status = 420;
			free_and_close_data(data); // this can go after we are done implementing
			*/
		}
	}
		printf("Command not found.\n");
		if (command)
			free(command);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WIFSIGNALED(status);
		free_and_close_data(data);

}
/*
0 		Successful execution 	 
1 		Catch generic errors 	
2 		Improper command usage 	
127 	The issue in path resolution
130 	Fatal error 	When interrupted by Ctrl+C
255 	Out of range 	When the exit code exceeds 255
*/