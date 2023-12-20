/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:57:20 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/18 12:26:52 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_nextline(char *buff)
{
	char	*next;
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	next = ft_calloc(((ft_strlen(buff)) - i + 1), sizeof(char));
	i++;
	while (buff[i])
	{
		next[a] = buff[i];
		i++;
		a++;
	}
	free (buff);
	return (next);
}

char	*ft_get_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_freemebaby(char *result, char *buff)
{
	char	*temp;

	temp = ft_strjoin (result, buff);
	free (result);
	return (temp);
}

char	*ft_read_file(int fd, char *result)
{
	int		bytes_read;
	char	*buff;

	bytes_read = 1;
	if (!result)
		result = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buff);
			free (result);
			return (NULL);
		}
		buff[bytes_read] = 0;
		result = ft_freemebaby(result, buff);
		if (ft_strchr(result, '\n'))
			break ;
	}
	free (buff);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*buff;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_read_file(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_get_line(buff);
	buff = ft_nextline(buff);
	return (line);
}
