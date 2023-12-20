/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:45:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/12/20 16:38:55 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_quotes(char * line)
{
	int		i;
	int		check;

	check = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			check += 1;
		if (check == 2)
			return(i+1);
		i++;	
	}
		return(0);
}

int check_token_syntax(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if ( str[0] == '|')
			return(1);
		if (str[0] == '<') 
			return(2);		
		if (str[0] == '>')
			return(3);
	}
	else if (ft_strlen(str) == 2)
	{
	if (str[0] == '<' && str[1] == '<')
		return (4);
	if (str[0] == '>' && str[1] == '>')
		return (5);
	}
	return(0);
}


char	*trimstr(char *str,int i)
{
	int		a;
	char  *returnstr;
	int start;
	
	start = i;
	a = 0;
	while (str[i])
	{
		i++;
		a++;
	}
	returnstr = ft_calloc(a + 1,sizeof(char));
	if (!returnstr)
		puterr(ALLOCERR);// exit with failure
	i = 0;
	while (str[start] != '\0')
	{
		returnstr[i] = str[start];
		i++;
		start++;
	}
	returnstr[i] = 0;
	return(returnstr);
}

char *tokenizer(char **line)
{
	int		i;
	char *buffer;

	i = 0;
	if(*line[i] == 0)
		return(NULL);
	while ((*line)[i] == '>' || (*line)[i] == '|' || (*line)[i] == '<')
		i++;
	buffer = ft_substr(*line,0,i);
	*line = trimstr(*line,i);
	if (!check_token_syntax(buffer))
		puterr(SYNERR);	
	return(buffer);
}
void 	print_words(t_words **words)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (words[i] != NULL)
	{
		printf("word: %s\n",words[i]->word_clean);
		printf("token: %s\n",words[i]->token_after_word);
		printf("num_of_elements: %d\n",words[i]->num_of_elements);
		printf("redirection: %s\n",words[i]->redirection->whole_command);
		printf("fd_in: %d\n",words[i]->redirection->fd_in);
		printf("fd_out: %d\n",words[i]->redirection->fd_out);
		printf("quotes_case: %d\n",words[i]->quotes_case);
		printf("\n");
		printf("\n");

		
		i++;
	}
}

int get_num_of_pipes(char * str)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (str[a])
	{
		if (str[a] == '|')
			i++;
		a++;
	}	
	return(i);
}

t_words	**init_word_stack(char *line, t_words **words)
{
	int	i;
	int	b;
	
	b = 0;
	i = 0;

	/*
	Still have to check for BS input 
	*/
	words = ft_calloc(get_num_of_pipes(line) + 2, sizeof(t_words *));
	while (line[i])
	{
		words[b] = ft_calloc(1, sizeof(t_words));
		if (!words[b])
			puterr(ALLOCERR);// exit with failure
		i = 0;
		if (!is_in_quotes(line))
			while (line[i] && line[i] != '|')
				i++;
		else
		{
			i = is_in_quotes(line);
			words[b]->quotes_case = 1;
		}
		words[b]->word = ft_substr(line,0,i);
		line = trimstr(line,i);
		if (line[0] != '\0')
			words[b]->token_after_word = tokenizer(&line);
			words[b]->redirection = ft_calloc(1, sizeof(t_redirection ));
		if (ft_strchr(words[b]->word, '>') || ft_strchr(words[b]->word, '<'))
		{
			words[b]->redirection->whole_command = ft_strdup(words[b]->word);
			words[b]->redirection->fd_in = 0;
			words[b]->redirection->fd_out = 1;
		}
		else
			words[b]->redirection->whole_command = NULL;
		b++;
		i = 0;
	}
	words[b] = NULL;
	while (words[i] != NULL)
		words[i++]->num_of_elements = b;
	clean_words(words);
	free_dirty_words(words);
	print_words(words);
	return(words);
}