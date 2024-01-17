/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/17 17:02:46 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(char **split_command,t_data *data)
{

	int pid;
	int status;
	char	*command;
	char	**args;

	args = split_command;//ft_split(clean_word, ' ');
	command = ft_strjoin("/bin/",split_command[0]); // still have to check if that exists
	if ((pid = fork()) == -1)
	perror("fork error");
	else if (pid == 0) 
	{
		execve(command, split_command, data->envp);
		free(command);
		printf("Return not expected. Must be an execve error.\n");
		//free_and_close_data(data,1);
		exit(1);
	}
	else
	{
		free(command);
		//waitpid(pid, &status, 0);
		//status = (status & 0x7f00) >> 8;
		//if (status == 1)
			//free_and_close_data(data,2);
	}

}