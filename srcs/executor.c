/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/06 13:05:07 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/executor.h"

void	executor(char *clean_word, char **envp)
{
	int	i;
	int pid;
	(void)envp;
	i = 0;
	char **argv = ft_split(clean_word,' ');
	 if ((pid = fork()) == -1)
        perror("fork error");
     else if (pid == 0) 
	 {
        execve(ft_strjoin("/bin/",argv[0]),argv, envp);
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