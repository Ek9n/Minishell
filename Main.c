/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/10/05 19:33:41 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*trimstr(char *str,int i)
{
	int		a;
	int		start;
	char  *returnstr;
	start = i;
	while (str[i])
	{
		a++;
		i++;
	}
	returnstr = ft_calloc(a + 1,sizeof(char));
	i = 0;
	while(start < a)
	{
		returnstr[i] = str[start];
		i++;
		start++;
	}
	returnstr[i] = 0;
	return (returnstr);
}
t_words	*init_word_stack(char *line)
{
	int		i;
	int		a;
	char *buffer;
	t_words	*words;

	words  = ft_calloc(1,sizeof(t_words));
	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] != ">" || line[i] != "&" || line[i] != "|" || line[i] != "<")
			ft_strlcpy(buffer,line,i);	
		else if (line[i])
		{
			trimstr(line,i);
			words->word = buffer;
			free(buffer);
		}
	}
}
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void)	context;
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
		printf("slash");
	fflush(0);
}

int	main(void)
{
	struct sigaction	act;
	
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	init_word_stack(readline());
	while (1)
	 	pause();
	
}
