#include "../includes/minishell.h"

char	*echo(char *word)
{
	bool	flag;
	flag = false;
	word += 5;
	// printf("InEcho:%s\n", word);
	if (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	else if (*(word + 3) == '\0' && ft_strcmp("-n", word) == 0)
	{
		printf("(echo) landed here somehow\n");
	}
	if (flag)
		return (ft_savef("%s",word));
	return (ft_savef("%s\n", word));
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

int	cd(char **split_cmds, char ***env)
{
	char 	**buffer;

	// printf("in cd:%s\n", split_cmds[1]);

	buffer = calloc(3, sizeof(char *));
	buffer[0] = ft_strdup("export");
	buffer[1] = ft_strjoin("OLDPWD=", getpwd());

	export(buffer, env);
	// printf("CD_IN:%s\n", dir);
	// if (dir[2] == ' ')
	// 	dir += 3;
	// pwd = ft_strjoin("export OLDPWD=", getpwd());
	// if (ft_strcmp(dir, "~") == 0 || ft_strcmp(dir, "cd") == 0)
	// 	dir = ft_strdup(getenv("HOME"));
	// if (split_cmds[2] != 0)
	// {

	// }
	if (chdir(split_cmds[1]) != 0) 
    {
        perror("(cd) No valid pathname!");
		// free(buffer[0]);
		// free(buffer[1]);
		// free(buffer);
		return (EXIT_FAILURE);
    }

	// free(buffer[1]);

	buffer[1] = ft_strjoin("PWD=", getpwd());
	export(buffer, env);
	// free(buffer[0]);
	// free(buffer[1]);
	// free(buffer);

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
