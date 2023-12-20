/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/18 18:24:15 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(char *clean_word, char **envp)
{

	int pid;
	(void)envp;

	char	**args = ft_split(clean_word, ' ');

	if ((pid = fork()) == -1)
	perror("fork error");
	else if (pid == 0) 
	{
		execve(ft_strjoin("/bin/",args[0]), args, NULL);
		printf("Return not expected. Must be an execve error.\n");
	}
	else
	{
		waitpid(0, NULL, 0);
	}

}
