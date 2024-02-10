/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:53:46 by hstein            #+#    #+#             */
/*   Updated: 2024/02/10 15:25:46 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ek1n@FlyingLamb7:~/42Berlin/Github/Minishell$ echo "" A
// //  A
// int	echo(t_words *node)
// {
// 	int		i;
// 	char	*tmp;
// 	bool	flag;

// 	flag = false;
// 	printf("InEcho:%s\n", node->split_command[0]);
// 	if (node->num_of_elements == 1)
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	i = 0;
// 	while (ft_strcmp(node->split_command[++i], "-n") == 0)
// 	{
// 		if (node->num_of_elements == 2)
// 			return (0);
// 		flag = true;
// 	}
// 	// if num > 3?
// 	tmp = ft_strdup(node->split_command[i]);
// 	while (node->split_command[++i])
// 	{
// 		tmp = ft_strjoinfree(tmp, node->split_command[i]);
// 	}
// 	if (flag)
// 	{
// 		printf("%s", tmp);
// 	}
// 	else
// 		printf("%s\n", tmp);
// 	free(tmp);
// 	return (0);
// }

int	ft_strxcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && s2[i])
	{
		// printf("%d\n", s1[i]);
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	cmp_keywordx(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword) - ft_strlen(str);
	if (len < 0)
		len *= -1;
	if ((ft_strcmp(keyword, str) == 0) && len == 0)
		return (1);
	return (0);
}

int	echo(t_words *node)
{
	char 	*tmp;
	char 	*word;
	bool	flag;

	flag = false;

		// printf("in echo|%s|\n", node->command);
		// printf("in echo|%d|\n", ft_strlen(node->command));
	if (node->num_of_elements == 1 && !cmp_keywordx("echo", node->command))
	{
		printf("-minishell.c (echo) %s: command not found\n", node->command);
		return (1);
	}
	tmp = ft_strdup(node->command);
	word = tmp;
	word += 5;
	while (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	if (*(word + 3) == '\0' && ft_strcmp("-n", word) == 0)
	{
		flag = true;
		word += 2;
	}
	if (flag)
	{
		printf("%s", word);
		fflush(0);
	}
	else
		printf("%s\n", word);
	free(tmp);
	return (0);
}


char	*getpwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd() error");
		return (NULL);
	}
	return (buf);
}

// int	cd(char **split_cmds, char ***env)
int	cd(t_words *node, t_data *data)
{
	char	*dir;
	char	*pwd;
	char	*oldpwd;
	char 	**buffer;
	int		i;
// printf("cdIN:%s\n", node->split_command[1]);
	if (node->num_of_elements > 2)
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	// printf("CD: NUMS%d\n", node->num_of_elements);
	if (node->num_of_elements == 2 && !ft_strcmp(node->split_command[1], ""))
		return (EXIT_SUCCESS);

	
	oldpwd = ft_strjoin("OLDPWD=", getpwd());

	if (node->split_command[1] == NULL || ft_strcmp(node->split_command[1], "~") == 0)
		dir = ft_strdup(getenv("HOME"));
	else
		dir = ft_strdup(node->split_command[1]);

	if (chdir(dir) != 0) 
    {
        perror("(cd) No valid pathname");
		free(dir);
		free(oldpwd);
		i = -1;
		return (EXIT_FAILURE);
    }

	pwd = ft_strjoin("PWD=", getpwd());
	buffer = calloc(4, sizeof(char *));
	buffer[0] = ft_strdup("export");
	buffer[1] = oldpwd;
	buffer[2] = pwd;
	export(buffer, &data->envp);
	free(buffer[0]);
	free(buffer[1]);
	free(buffer[2]);
	free(buffer);
	free(dir);
	
	return (EXIT_SUCCESS);
}

int	ls(char *dir)
{
	pid_t p = fork();

	if(p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	if (p == 0)
	 {
		char *ls_argv[] = {"ls", dir, NULL};
		execv("/bin/ls", ls_argv);
		perror("execv failed");
		exit(1);
	}
	return 0;
}

void	unset(char **split_cmds, char ***env)
{
	int		i;

	i = 1;
	while (split_cmds[i])
	{
		delete_env_var(split_cmds[i], env);
		i++;
	}
}

// int	vars_are_valid(char *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (cmd[++i])
// 	{
// 		if (cmd[i] == ' ')
// 			space =
// 		if (cmd[i] == '=' && i != 0)
// 			equals = true;
// 	}
// 	if (cnt )
// 	return (0);
// }

void	export(char **split_cmds, char ***env)
{
	int	i;
	// printf("exportIn:%s\n", split_cmds[0]);
	// printf("exportIn:%s\n", split_cmds[1]);
	// printf("exportIn:%s\n", split_cmds[2]);
	// printf("exportIn:%s\n", split_cmds[3]);
	if (split_cmds[1] == NULL)
	{
		i = 0;
		while (env[0][i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env[0][i], 1);
			printf("\n");
			i++;
		}
	}
	else
	{
		i = 1;
		while (split_cmds[i])
		{
			purge_arr(split_cmds[i], env);
			add_env_var(split_cmds[i], env);
			i++;
		}
	}
}
// A = 23 should not work

