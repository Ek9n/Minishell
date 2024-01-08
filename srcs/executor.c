/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/08 10:53:49 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(char *clean_word,t_data *data)
{

	int pid;
	int status;
	char	*command;
	char	**args;
	int		i;


	i = 0;
	command = NULL;
	args = ft_split(clean_word, ' ');
	while (args[i] != NULL)
	{
		if (ft_strnstr(args[i], "/bin/", 5) != NULL)
			command = ft_strdup(args[0]);
		else
			command = ft_strjoin("/bin/",args[0]);
		i++;
	}
	if ((pid = fork()) == -1)
	{
		g_exit_status = 1;
		perror("fork error");
	}
	else if (pid == 0 && g_exit_status == 0) 
	{
		execve(command, args, data->envp);
		free(command);
		printf("Return not expected. Must be an execve error.\n");
		g_exit_status = 420;
		free_and_close_data(data);
	}
	else
	{
		if (command)
			free(command);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WIFSIGNALED(status);
	}
		free_and_close_data(data);

}