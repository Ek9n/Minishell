/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:18 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/07 19:20:38 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
//command1 < input1.txt > output1.txt //2> error.txt < input2.txt > output2.txt < input3.txt
/*1st step:
cat reads input 1 
2nd: 
cat outputs to output1
*/

int		check_for_redirection(t_words **words)
{
	int	i;
	
	while (words[i])
	{
		while (words[i]->redirection > 1)
		{
			i++;
			if(words[i]->redirection <= 1)
				init_redirection(words,i);
		}
		i++;
	}
	return(0);
}
void	init_redirection(t_words **words, int i)
{
	t_redirections	**redir;
	
	redir = ft_calloc(i,sizeof(t_redirections**));
	i = 0;
	int a = 0; 
	while (words[i])
	{
		if (words[i]->redirection == 2)
			redir[a]->fd_in = open(words[i + 1]->word,O_RDONLY);
			//separate function to initialize FDs maybe, then decide how to navigate the the whole words struct, if to shorten it, etc...
	}
	
	
}

/*
typedef struct t_words
{
	char	*word; //julius Lexer
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	char 	**enviroment;
	int		redirection;
}		t_words;
*/
/*
< = 2
> = 3
<< = 4
>> = 5
*/