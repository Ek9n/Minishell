/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/10/13 13:36:59 by jfoltan          ###   ########.fr       */
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
	if (ft_strlen(str) == 2)
		if (str[0] == '<' || str[0] == '>' || str[0] == '&' || str[0] == '|')
			return(1);		
	else if (ft_strlen(str) == 3)
	{
	if (str[0] == '<' && str[1] == '<')
		return (1);
	if (str[0] == '>' && str[1] == '>')
		return (1);
	if (str[0] == '&' && str[1] == '&')
		return (1);
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
	while ((*line)[i] == '>' || (*line)[i] == '&' || (*line)[i] == '|' || (*line)[i] == '<')
		i++;
	buffer = ft_substr(*line,0,i);
	*line = trimstr(*line,i);
	if (!check_token_syntax(buffer));
		puterr(SYNERR);	
	return(buffer);
}
t_words	**init_word_stack(char *line,t_words **words)
{
	int		i;
	static int b = 0;
	
	i = 0;
		words = ft_calloc(1, sizeof(t_words));
		while (line[i] != '\0')
		{
		words[b] = ft_calloc(1, sizeof(t_words));
		if (!words[b])
			puterr(ALLOCERR);// exit with failure
		i = 0;
		if (!is_in_quotes(line))
			while (line[i] && (line[i] != '>' && line[i] != '&' && line[i] != '|' && line[i] != '<'))
				i++;
		else
		{
			i = is_in_quotes(line);
			words[b]->quotes_case = 1;
		}
		words[b]->word = ft_substr(line,0,i);
		line = trimstr(line,i);
		words[b]->token_after_word = tokenizer(&line);
		words[b]->num_of_elements = b;
		b++;
		i = 0;
		}
	words[b] = NULL;
	return(words);
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
	t_words **words;
	char * input;
	int		b;

	b = 0;
	words = NULL;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	input = readline("Minishell>>: ");
	words = init_word_stack(input,words); // I guess separation is done, now to implement syntax and quote checks
	
	while (words[b] != NULL)
	{
	printf("word: %s at index: %d\n",words[b]->word,b);
	printf("Token: %s at index %d\n",words[b]->token_after_word,b);
	b++;
	}
	
}
