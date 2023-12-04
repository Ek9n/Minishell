// #include "minishell.h"
#include "../libft/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;
	
	n = ft_strlen(s1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**arrdup(char **enviroment)
{
	int		rows;
	int		i;
	char	**dup;

	rows = 0;
	while (enviroment[rows])
		rows++;
	i = 0;
	dup = ft_calloc(rows + 2, sizeof(char **));
	if (!dup)
		return (NULL);
	rows = 0;
	while (enviroment[rows] != NULL)
	{
		dup[rows] = ft_strdup(enviroment[rows]);
		if (dup[rows] == NULL)
			return (NULL);
		rows++;
	}
	dup[rows] = NULL;
	return (dup);
}

void	printenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd(env[i], 1);
		printf("\n");
		i++;
	}
}

int	cntenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	freeenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**delete_env_var(char *name, char **env)
{
	int	size = cntenv(env);

	char	**new_env = 0;

	new_env = ft_calloc(size, sizeof(char *));
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp(name, env[i]) != 0)
		{
			new_env[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

// char	**add_env_var(char *name, char **env)
// {
// 	int		size = cntenv(env);
// 	int		i;
// 	char	**new_env;

// 	new_env = ft_calloc(size + 1, sizeof(char *));
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		new_env[i] = env[i];
// 		i++;
// 	}
// 	new_env[i] = name;
// 	free(env);
// 	return (new_env);
// }
void	add_env_var(char *name, char ***env)
{
	int		size = cntenv(*env);
	int		i;
	char	**new_env;

	new_env = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env[0][i] != NULL)
	{
		new_env[i] = env[0][i];
		i++;
	}
	new_env[i] = name;
	free(*env);
	*env = new_env;
}
	// else if (cmp_keyword("export", INstruct->word_clean))
	// {
	// 	export(INstruct->word_clean);
	// }

void	export(char *str, char ***env)
{
	// char	**env_new;
	char	**cmds;
	int	i;

	cmds = ft_split(str, ' ');
	i = 0;
	if (cmds[i + 1] == NULL)
		printf("print envs here in exportstyle!\n");
	while (cmds[i])
	{
		
		add_env_var(cmds[i], env);
		i++;
	}


}

int	main(int argc, char **argv, char **env)
{
	char	**env_lst = arrdup(env);
	// ft_putstr_fd(env_lst[0], 1);
	printf("CNT:%d\n", cntenv(env_lst));
	// printenv(env_lst);
	// env_lst = delete_env_var("OLDPWD", env_lst);
	// char str[] = "HELLOWORLD";
	char *str;
	str = malloc(50);
	str = ft_strdup("H=55");

	// env_lst = add_env_var(str, env_lst);
	add_env_var(str, &env_lst);
	// export(str, &env_lst);
	// delete_env_var("OLDPWD", &env_lst);
	printf("CNT:%d\n", cntenv(env_lst));

	printenv(env_lst);

	freeenv(env_lst);
	return (0);
}
