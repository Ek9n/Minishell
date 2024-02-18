/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:38:38 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/18 14:54:46 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	conditions(char **dirty_word, char **tmp_word, int *ij, bool start)
{
	static int	last_quote;
	static bool	quotes;

	if (start == true)
	{
		last_quote = 0;
		quotes = false;
	}
	detect_quote(&dirty_word[0][ij[0]], &quotes, &last_quote);
	if (!quotes && redir_case(&dirty_word[0][ij[0]]) == 1)
	{
		tmp_word[0][ij[1]++] = ' ';
		tmp_word[0][ij[1]++] = dirty_word[0][(ij[0])++];
		tmp_word[0][ij[1]++] = ' ';
		detect_quote(&dirty_word[0][ij[0]], &quotes, &last_quote);
	}
	else if (!quotes && redir_case(&dirty_word[0][ij[0]]) == 2)
	{
		tmp_word[0][ij[1]++] = ' ';
		tmp_word[0][ij[1]++] = dirty_word[0][(ij[0])++];
		tmp_word[0][ij[1]++] = dirty_word[0][(ij[0])++];
		tmp_word[0][ij[1]++] = ' ';
		detect_quote(&dirty_word[0][ij[0]], &quotes, &last_quote);
	}
}

static void	check_str(char **dirty_word, char **tmp_word)
{
	bool	start;
	int		ij[2];

	start = true;
	ij[0] = 0;
	ij[1] = 0;
	while (dirty_word[0][ij[0]])
	{
		conditions(dirty_word, tmp_word, ij, start);
		start = false;
		tmp_word[0][ij[1]] = dirty_word[0][ij[0]];
		ij[0]++;
		ij[1]++;
	}
	tmp_word[0][ij[1]] = '\0';
}

void	redirection_space_extender(char **dirty_word)
{
	int		last_quote;
	bool	quotes;
	char	*tmp_word;

	if (*dirty_word != NULL)
	{
		tmp_word = malloc(ft_strlen(*dirty_word) * 2 + 1);
		check_str(dirty_word, &tmp_word);
		free(*dirty_word); //..why it doesn't work like that?
		*dirty_word = ft_strdup(tmp_word);
		// strcpy(tmp_word, *dirty_word);
		free(tmp_word);

	}
}
    // if (*dirty_word != NULL) {
    //     // Berechnen der neuen Größe für tmp_word
    //     int new_size = ft_strlen(*dirty_word) * 2 + 1; // +1 für den Nullterminator

    //     // Allokieren von Speicher für tmp_word
    //     tmp_word = malloc(new_size);
    //     if (tmp_word == NULL) {
    //         // Fehlerbehandlung, wenn malloc fehlschlägt
    //         // Hier muss entschieden werden, wie mit dem Fehler umgegangen wird
    //         return; // Zum Beispiel: Rückkehr oder anderes Verhalten
    //     }

    //     // Kopieren des Inhalts von *dirty_word in tmp_word
    //     strcpy(tmp_word, *dirty_word);

    //     // Freigeben des ursprünglichen Speichers von *dirty_word
    //     free(*dirty_word);

    //     // Kopieren des Inhalts von tmp_word in *dirty_word
    //     *dirty_word = ft_strdup(tmp_word);

    //     // Freigeben des temporären Speichers von tmp_word
    //     free(tmp_word);
    // }
//char 	*clean_spaces_in_command(char *command)
//{
//	char	*tmp_clean;
//	int		i;
//	int		j;

//	tmp_clean = malloc(ft_strlen(command) + 1);
//	i = 0;
//	j = 0;
//	i += skip_spaces(command);
//	while (command[i] != '\0')
//	{
//		if (command[i] == ' ' || command[i] == '\t')
//		{
//			i += skip_spaces(&command[i]);
//			tmp_clean[j++] = ' ';
//		}
//		else
//			tmp_clean[j++] = command[i++];
//	}
//	while (tmp_clean[--j] == ' ');
//	tmp_clean[j + 1] = '\0';
//	free(command);
//	command = ft_strdup(tmp_clean);
//	free(tmp_clean);
//		return(command);

void	clean_spaces_in_command(char **command)
{
	char	*tmp_clean;
	int		i;
	int		j;

	tmp_clean = malloc(ft_strlen(*command) + 1);
	i = 0;
	j = 0;
	i += skip_spaces(*command);
	while (command[0][i] != '\0')
	{
		if (command[0][i] == ' ' || command[0][i] == '\t')
		{
			i += skip_spaces(&command[0][i]);
			tmp_clean[j++] = ' ';
		}
		else
			tmp_clean[j++] = command[0][i++];
	}
	while (tmp_clean[--j] == ' ')
		;
	tmp_clean[j + 1] = '\0';
	free(*command);
	*command = ft_strdup(tmp_clean);
	free(tmp_clean);
}
