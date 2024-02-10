/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/10 17:05:07 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int Executor(t_data *data)
{
	// printf("nopipes:%d\n", data->numb_of_pipes);
	// printf("ExecutorIn:%s\n", data->nodes[0]->split_command[0]);
	int	i;

	i = -1;
	int a = 0;
	while (data->nodes[++i])
	{
		get_fds(data, i);
		//while (data->nodes[i]->split_command[a])
		//{	
		//	ft_putstr_fd(data->nodes[i]->split_command[a],STDOUT_FILENO);
		//	a++;
		//}
		//a = 0;	
	}
	
		// printf("ExecutorOut:%s\n", data->nodes[0]->split_command[0]);
	if (data->numb_of_pipes == 0)
	{
		single_command(data, 0);
	}
	else if (data->numb_of_pipes != 0 && g_exit_status == 0)
		piperino9(data->nodes, data);
	return (0);
}

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	if (!keyword || !str)
		return (-1);
	len = ft_strlen(keyword);
	if (ft_strlen(str) > 0 && (ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

int	cnt_bytes(char **arr)
{
	int	i;
	int	bytes;

	bytes = 0;
	i = -1;
	while (arr[++i])
		bytes += ft_strlen(arr[i]) + 1;
	bytes += (i + 1) * sizeof(char *);
	return (bytes);
}

int	single_command(t_data *data, int i)
{
	// printf("in single_command:%s\n", data->nodes[i]->command);
	// printf("in single_command:%s\n", data->nodes[i]->split_command[0]);
	// printf("in single_command:%s\n", data->nodes[i]->split_command[1]);
// enum for checking alll keywords before... if it doesnt match -> print error
	if (data->nodes[i] && data->nodes[i]->split_command[0])
	{	
		if (cmp_keyword("echo", data->nodes[i]->command))
		{
			// printf("singlecommand -> echo\n");
			echo(data->nodes[i]);
		}
		else if (cmp_keyword("pwd",data->nodes[i]->split_command[0]))
		{
			data->nodes[i]->output = getpwd();
			printf("%s\n", data->nodes[i]->output);
		}
		else if (cmp_keyword("cd", data->nodes[i]->split_command[0]))
			cd(data->nodes[i], data);
		else if (cmp_keyword("export", data->nodes[i]->split_command[0]))
		{
			int b = -1;
			while (data->envp[++b]);
			printf("executerEnvVars1:%d|\n", b);

			export(data->nodes[i]->split_command, &data->envp);

			b = -1;
			while (data->envp[++b]);
			printf("executerEnvVars2:%d|\n", b);
		}
		else if (cmp_keyword("unset", data->nodes[i]->split_command[0]))
		{
			unset(data->nodes[i]->split_command, &data->envp);
			// unset(data->nodes[i]->split_command[1], &data->envp);
		}
		else if (cmp_keyword("env", data->nodes[i]->split_command[0]))
		{
			printf("single_command//env\n");
			printenv(data->envp);
		}
		else if (cmp_keyword("exit", data->nodes[i]->split_command[0]))
		{
			g_exit_status = 69;
			free_and_close_data(data);
		}
		else
		{
			// printf("(single_command) - exec_cmd\n");
			if (data->nodes[i]->split_command[0])
				exec_cmd(data->nodes[i]->split_command, data);
		}
	}
	return (0);
}

 int		check_for_only_tab_or_space(char *str)
 {
 	int	i;

 	i = 0;
 	while (str[i])
 	{
 		if (str[i] != ' ' && str[i] != '\t')
 			return (0);
 		i++;
 	}
 	return (-1);
 }

char **FIX_ME(char **split_command)
{
    char *temp_not_split;
    char **temp_split_one;
    char **old_split;
    char **new_split;
    int deli;
    int i;
    int a;
    int j;
	if (check_for_only_tab_or_space(split_command[0]) == -1)
		return (NULL);
    old_split = arrdup(split_command);
    temp_not_split = ft_strdup(split_command[0]);
    temp_split_one = ft_split(temp_not_split, ' ');
    deli = 0;
    i = 0;
    a = 0;
    while (split_command[0][i])
    {
        if (split_command[0][i] == ' ')
            deli++;
        i++;
    }
    i = 0;
    while (split_command[i])
        i++;
    new_split = malloc(sizeof(char *) * (i + deli + 1));
    i = 0;
    j = 0;
    while (temp_split_one[j])
    {
        new_split[i] = ft_strdup(temp_split_one[j]);
        i++;
        j++;
    }
    a = 1;
    while (old_split[a]) {
        new_split[i] = ft_strdup(old_split[a]);
        i++;
        a++;
    }
    new_split[i] = NULL;
    return new_split;
}
void	exec_cmd(char **split_command, t_data *data)
{
		int status;
		int		pid;
		char    *command;
        char    **path;
        int     i;
        
		//split_command = ft_split
		path = malloc(sizeof(char *) * 2);
		if (ft_strchr(split_command[0],' '))
			split_command = FIX_ME(split_command);
		if (split_command == NULL)
			return ;
		command = ft_strdup(split_command[0]);
		path[0] = ft_strdup("$PATH");
        path[1] = ft_strdup("\0");
        expand_vars(path, 0, data);
        path  = ft_split(path[0], ':');
        i = 0;
        while (path[i])
        {
                if (split_command[0][0] == '/' || (split_command[0][0] == '.' && split_command[0][1] == '/'))
                        {
                                command = ft_strdup(split_command[0]);
								break;
                        }
				if (split_command[0][0] == '.' && split_command[0][1] == '.' && split_command[0][2] == '/')
				{	
					command = ft_strdup(split_command[0]);
					break;
				}
                command = ft_strjoin(path[i],"/");
                command = ft_strjoin(command, split_command[0]);
                if (access(command,F_OK) == 0)
                        break ;
                i++;
        }
		if (access(command, F_OK) == 0)
        	while (true)
			{
           	     if (access(command, X_OK))
					{
							g_exit_status = 126;
							printf("Permission denied\n");
							break;
					}
               	 if ((pid = fork()) == -1)
               	 {
               	         g_exit_status = 1;
               	         perror("fork error");
							break;
					}
					else if (pid == 0 && g_exit_status == 0)
               	 {	
						// split_command++; <- this made it bugging
               	         // printf("cmd1:%s, path1:%s\n", split_command[1], command);
               	         // printf("cmd1:%s, path1:%s\n", split_command[2], command);
               	         // printf("cmd1:%s, path1:%s\n", split_command[3], command);
               	         execve(command, split_command, data->envp);
               	         /*free(command);
               	         printf("Return not expected. Must be an execve error.\n");
               	         g_exit_status = 420;
               	         free_and_close_data(data); // this can go after we are done implementing
               	         */
               	 }
               	 waitpid(pid, &status, 0);
               	 if (WIFEXITED(status))
               	         g_exit_status = WEXITSTATUS(status);
               	 else if (WIFSIGNALED(status))
               	         g_exit_status = 130 + WIFSIGNALED(status);
				break;
			}
        else
        {
                printf("%s : No such file or directory\n",split_command[0]);
                g_exit_status = 127;
        }
        if (command)
                free(command);
}
/*
0 		Successful execution 	 
1 		Catch generic errors 	
2 		Improper command usage 	
127 	The issue in path resolution
130 	Fatal error 	When interrupted by Ctrl+C
255 	Out of range 	When the exit code exceeds 255
*/

