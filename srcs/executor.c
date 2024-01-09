/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/01 14:20:47 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *clean_word,t_data *data)
{

	int pid;
	int status;
	char	*command;
	char	**args;

	args = ft_split(clean_word, ' ');
	command = ft_strjoin("/bin/",args[0]);
	if ((pid = fork()) == -1)
	perror("fork error");
	else if (pid == 0) 
	{
		execve(command, args, data->envp);
		free(command);
		printf("Return not expected. Must be an execve error.\n");
		free_and_close_data(data,1);
	}
	else
	{
		free(command);
		waitpid(pid, &status, 0);
		status = (status & 0x7f00) >> 8;
		if (status == 1)
			free_and_close_data(data,2);
	}

}