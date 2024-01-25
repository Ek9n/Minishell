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

	len = abs(ft_strlen(keyword) - ft_strlen(str));
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

		// printf("%s|\n", node->command);
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
		printf("%s", word);
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

	if (node->num_of_elements > 2)
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	printf("CD: NUMS%d\n", node->num_of_elements);
	if (node->num_of_elements == 2 && !ft_strcmp(node->split_command[1], ""))
		return (EXIT_SUCCESS);

	buffer = calloc(3, sizeof(char *));
	buffer[0] = ft_strdup("export");

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
		while (buffer[++i])
			free(buffer[i]);
		free(buffer);
		return (EXIT_FAILURE);
    }
	else
	{
		pwd = ft_strjoin("OLDPWD=", getpwd());

		// free(buffer[1]);

		buffer[1] = ft_strjoin("PWD=", getpwd());
		export(buffer, &data->envp);
		export(buffer, &data->envp);
		// free(buffer[0]);
		// free(buffer[1]);
		// free(buffer);
		free(dir);
		free(pwd);
		free(oldpwd);
	}
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

void	export(char **cmds, char ***env)
{
	int	i;

	if (cmds[1] == NULL)
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
		while (cmds[i])
		{
			purge_arr(cmds[i], env);
			add_env_var(cmds[i], env);
			i++;
		}
	}
}
