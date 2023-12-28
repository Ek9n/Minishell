/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:18 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/28 14:03:30 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

//cat < input1.txt > output1.txt 2> error.txt < input2.txt > output2.txt < input3.txt
/*1st step:
cat reads input 1 
2nd: 
cat outputs to output1
*/
/*
< = 2
> = 3
<< = 4
>> = 5
*/

void	init_redirection(t_words **words, int i)
{
	while (words[i])
	{
		/*
			if (words[i]->redirection == <)
		{
			words[i]->fd_in = open(words[i + 1]->word,O_RDONLY);	
			dup2(words[i]->fd_in, STDIN_FILENO);
		}
		if (words[i]->redirection == >)
		{
			words[i]->fd_out = open(words[i + 1]-> word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(words[i]->fd_out, STDOUT_FILENO);
		}
		if (words[i]-> redirection == <<)
			//ft_heredoc with readline
		if (words[i]-> redirection == >>)
			words[i]->fd_out = open(words[i + 1]-> word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		i++;
		*/
	}
}

int		check_for_redirection(t_words **words)
{/*
	int	i;
	
	i = 0;
	while (words[i] && words[i] -> redirection > 1)
		i++;
	init_redirection(words,i);
	return(0);*/
	return(0);
}