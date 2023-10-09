/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/10/09 14:22:05 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_redirection(char *str, int start)
{
	if (str[start] == '<' && str[start + 1] == '<')
		return(ft_strdup("<<"));
	if (str[start] == '>' && str[start + 1] == '>')
		return(ft_strdup(">>"));
	if (str[start] == '&' && str[start + 1] == '&')
		return(ft_strdup("&&"));
	return(NULL);
}
char	*trimstr(char *str,int i)
{
	int		a;
	char  *returnstr;
	returnstr = ft_calloc(i,sizeof(char));
	while(a < i)
	{
		returnstr[a] = str[a];
		a++;
	}
	returnstr[a] = 0;
	//printf("fg");
	return (returnstr);
}
char *tokenizer(char **line)
{
	int		i;
	char *buffer;

	i = 0;
	while (*line[i] && !(*line[i] != '>' && *line[i] != '&' && *line[i] != '|' && *line[i] != '<'))
		i++;
	buffer = ft_substr(*line,0,i);
	*line = trimstr(*line,i);
	return(buffer);
}
t_words	**init_word_stack(char *line,t_words **words)
{
	int		i;
	int		a;
	static int b = 0;
	i = 0;
	a = 0;
		if (!words[b])
			words[b]  = ft_calloc(1,sizeof(t_words));
		while (line[i])
		{
			a = i;
			while (line[i] && (line[i] != '>' && line[i] != '&' && line[i] != '|' && line[i] != '<'))
				i++;
		words[b]->word = ft_substr(line,a,i);
		line = trimstr(line,i);
		words[b]->token_after_word = tokenizer(&line); //edge case of >< <<< >>> etc have to handle correct input, probably after occupying the array, if special charcters are left, its a problem
		b++;
		init_word_stack(line,words);// initialize the array of stuff
		}
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
	words = ft_calloc(1,sizeof(t_words**));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	input = readline("Minishell>>: ");
	words = init_word_stack(input,words);
	while (words[b])
	{
	printf("word: %s at index: %d\n",words[b]->word,b);
	printf("Token: %s at index %d\n",words[b]->token_after_word,b);
	b++;
	}
	
}
