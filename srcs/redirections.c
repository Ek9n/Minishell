/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:18 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/07 21:13:38 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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

int	ft_heredoc(char *delimiter, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	line = ft_calloc(1, sizeof(char));
	while (true)
	{
		line = readline("> ");
		expand_vars(&line,0,data);
		i = -1;
		while (line[++i] != '\0')
		{
			if (line[i] == '$')
				line[i] = 26;
		}
		i = -1;
		while (line[++i] != '\0')
		{
			if (line[i] == 26)
				expand_vars(&line, i, data);
		}
		if (ft_strcmp(line, delimiter) == 0)
			break;	//add variable expansion
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (fd);
}

void	get_fds(t_data *data,int i)
{
	int a;
// printf("getfdIn:%s\n", data->nodes[i]->split_command[0]);
	a = 0;
	while (data->nodes[i]->split_command[a])
	{	
		if (check_token_syntax(data->nodes[i]->split_command[a]) == 4)
			{
				ft_heredoc(data->nodes[i]->split_command[a + 1],data);
				break;
			}
			else
				a++;
	}
	a = 0;
	while (data->nodes[i]->split_command[a])
	{
		if (check_token_syntax(data->nodes[i]->split_command[a]) == 3) // >
		{
			data->nodes[i]->fd_out = open(data->nodes[i]->split_command[a + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (data->nodes[i]->fd_out == -1)
			{
				dup2(data->original_fd_in, STDIN_FILENO);
				dup2(data->original_fd_out, STDOUT_FILENO);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed\n", 1);
				g_exit_status = 1;
			}	
			data->nodes[i]->split_command[a][0] = 0;
			data->nodes[i]->split_command[a + 1][0] = 0;
			data->nodes[i]->command = ft_join(data->nodes[i]->split_command);
			dup2(data->nodes[i]->fd_out, STDOUT_FILENO);	
			//close(data->nodes->redirection->fd_out);
		}
		if (check_token_syntax(data->nodes[i]->split_command[a]) == 5) // >
		{
			data->nodes[i]->fd_out = open(data->nodes[i]->split_command[a + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (data->nodes[i]->fd_out == -1)
			{
				dup2(data->original_fd_in, STDIN_FILENO);
				dup2(data->original_fd_out, STDOUT_FILENO);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed\n", 1);
				g_exit_status = 1;
			}	
			data->nodes[i]->split_command[a][0] = 0;
			data->nodes[i]->split_command[a + 1][0] = 0;
			data->nodes[i]->command = ft_join(data->nodes[i]->split_command);
			dup2(data->nodes[i]->fd_out, STDOUT_FILENO);
			//close(data->nodes->redirection->fd_out);
		}
		if (check_token_syntax(data->nodes[i]->split_command[a]) == 2) // <
		{
			data->nodes[i]->fd_in = open(data->nodes[i]->split_command[a + 1], O_RDONLY);
			if (data->nodes[i]->fd_in == -1)
			{
				dup2(data->original_fd_in, STDIN_FILENO);
				dup2(data->original_fd_out, STDOUT_FILENO);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed, file doesnt exist probably\n", 1);
				g_exit_status = 1;
			}
			data->nodes[i]->split_command[a][0] = 0;
			data->nodes[i]->split_command[a + 1][0] = 0;
			data->nodes[i]->command = ft_join(data->nodes[i]->split_command);
			dup2(data->nodes[i]->fd_in, STDIN_FILENO);
		}
		if (check_token_syntax(data->nodes[i]->split_command[a]) == 4) // <<
		{ 
			data->nodes[i]->fd_in = open(".heredoc", O_RDONLY);
			if (data->nodes[i]->fd_in == -1)
			{
				dup2(data->original_fd_in, STDIN_FILENO);
				dup2(data->original_fd_out, STDOUT_FILENO);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("Heredoc failed to create a temp file.\n", 1);
				g_exit_status = 1;
			}
			data->nodes[i]->split_command[a][0] = 0;
			data->nodes[i]->split_command[a + 1][0] = 0;
			data->nodes[i]->command = ft_join(data->nodes[i]->split_command);
			dup2(data->nodes[i]->fd_in, STDIN_FILENO);
		}
		a++;
	}
		data->nodes[i]->command = ft_join(data->nodes[i]->split_command); //free not sure if we need it ? 
// printf("getfdOut1:%s\n", data->nodes[i]->split_command[0]);
		data->nodes[i]->split_command = ft_split(data->nodes[i]->command, ' ');
// printf("getfdOut2:%s\n", data->nodes[i]->split_command[0]);
}

