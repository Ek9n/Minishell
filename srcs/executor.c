/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/10 13:42:52 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(char *clean_word, char **envp)
{
	// int	i;
	int pid;
	(void)envp;
	// i = 0;
	char	**args = ft_split(clean_word, ' ');
	// printf("->%s\n", clean_word);
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
	/*while (envp[i])
	{
		printf("value: %s\n",envp[i]);
		fflush(0);
		i++;
	}*/
}
