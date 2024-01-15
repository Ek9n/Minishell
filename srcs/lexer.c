/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:45:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/15 17:50:09 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
int quotes_start(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			return(i);
		i++;
	}
	return(0);
}
int quotes_end(char *line, int i)
{
	int a;

	a = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			return(a);
		i++;
		a++;
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
int	is_redirection(char 	*words)
{
	int i;
	int start;
	int end;

	if ()
	start = quotes_start(words);
	end = quotes_end(words, start) + start;
	i = 0;
	while (words[i])
	{
		if (words[i] == '>' || words[i] == '<')
			if ( i < start || i > end)
				return(1);
		i++;
	}
	return(0);
}
void do_redirection_stack(t_words *words)
{
	int start;
	int end;
	char *buffer;
	//redirection_space_extender(&words->word); have to rewrite this
	if (words->quotes_case == 1)
		{
			start = quotes_start(words->word);
			end = quotes_end(words->word, start) + start;
			buffer = ft_substr(words->word, start, end);
				
		}
	words->redirection = ft_calloc(1, sizeof(t_redirection ));
	words->redirection->whole_command = ft_strdup(words->word);
	words->redirection->split_command = ft_split(words->word, ' ');
	words->redirection->fd_in = 0;
	words->redirection->fd_out = 1;
}
t_words	**init_word_stack(char *line)
{
	int	i;
	int	b;
	t_words **words;

	b = 0;
	i = 0;

	//asd"sadad"adsdas << 
	//Still have to check for BS input 
---	check_num_of_quotes(line);
----replace_spaces_in_quotes(line); // HERE BITCH
----replace_pipes_in_quotes(line); // HERE BITCH
----split_by_pipe(line)
	words = ft_calloc(get_num_of_pipes(line) + 2, sizeof(t_words *));
	while (split_command[i])
	{
		words[b] = ft_calloc(1, sizeof(t_words));
		if (!words[b])
			puterr(ALLOCERR);// exit with failure
		i = 0;
---		extend spaces for redirection(split_command[i]);
----	clean_spaces(split_command[i]); (clean_words)
----	split by spaces(words[b]->word_clean);
----	bring back da spaces and da pipes(yomama);
---		expand_vars;
---get_rid_of_quotes
		//while (line[i] && line[i] != '|')
		//	i++;
		//words[b]->word = ft_substr(line,0,i);
		//line = trimstr(line,i);
		
		//if (is_in_quotes(words[b]->word))
			//words[b]->quotes_case = 1;
		
		//if (line[0] != '\0')
			//words[b]->token_after_word = tokenizer(&line); //,aybe just '|' is enough, but could be good for error check
		//if (is_redirection(words[b]->word)) // add errorchecking: >>> >>23 ...
			//do_redirection_stack(words[b]);
----	if_theres_redirection
----	do redireciton
		b++;	
		i = 0;
	}
	words[b] = NULL;
	while (words[i] != NULL)
		words[i++]->num_of_elements = b;
	i = 0;
	// This checks if there are odd amount of quotes in the words:
	i = -1;
	while (words[++i])
	{
		int	quotes = 0;
		int	j = -1;
		while (words[i]->word[++j])
		{
			if (words[i]->word[j] == '\'' || words[i]->word[j] == '\"')
				quotes++;
		}
		if (quotes % 2 != 0)
		{
			puterr(SYNERR);
			printf("CMD is FUCKED\n");
		}
	}
	// printf("InLexer1:%s\n", words[0]->word);
	// printf("InLexer2:%s\n", words[1]->word);

	// free_dirty_words(words);
	return(words);
}




/*t_words	**init_word_stack(char *line, t_words **words)
{
	int	i;
	int	b;
	
	b = 0;
	i = 0;


	Still have to check for BS input 
		printf("HIER>%s<\n", line);

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
		redirection_space_extender(&words[b]->word);
		line = trimstr(line,i);
		printf("HIER>%s<\n", line);
		if (line[0] != '\0')
			words[b]->token_after_word = tokenizer(&line);
			words[b]->redirection = ft_calloc(1, sizeof(t_redirection ));
		if (ft_strchr(words[b]->word, '>') || ft_strchr(words[b]->word, '<')) // add errorchecking: >>> >>23 ...
		{
			words[b]->redirection->whole_command = ft_strdup(words[b]->word);
			words[b]->redirection->split_command = ft_split(words[b]->word, ' ');
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
	// This checks if there are odd amount of quotes in the words:
	i = -1;
	while (words[++i])
	{
		int	quotes = 0;
		int	j = -1;
		while (words[i]->word[++j])
		{
			if (words[i]->word[j] == '\'' || words[i]->word[j] == '\"')
				quotes++;
		}
		if (quotes % 2 != 0)
		{
			puterr(SYNERR);
			printf("CMD is FUCKED\n");
		}
	}
	// printf("InLexer1:%s\n", words[0]->word);
	// printf("InLexer2:%s\n", words[1]->word);

	// free_dirty_words(words);
	return(words);
}
*/