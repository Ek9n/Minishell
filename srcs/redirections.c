/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:18 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/06 13:55:38 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
//command1 < input1.txt > output1.txt 2> error.txt < input2.txt > output2.txt < input3.txt
void	init_redirection(t_words *words)
{
	
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