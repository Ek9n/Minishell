#include "minishell.h"

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

char	**add_env_var(char *name, char **env)
{
	int		size = cntenv(env);
	int		i;
	char	**new_env;

	new_env = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = name;
	free(env);
	return (new_env);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	**env_lst = arrdup(env);
// 	// ft_putstr_fd(env_lst[0], 1);
// 	printf("CNT:%d\n", cntenv(env_lst));
// 	// printenv(env_lst);
// 	// env_lst = delete_env_var("OLDPWD", env_lst);
// 	// char str[] = "HELLOWORLD";
// 	char *str;
// 	str = malloc(5);
// 	str[0] = 'H';
// 	str[1] = '=';
// 	str[2] = 'Y';
// 	str[3] = '\0';

// 	env_lst = add_env_var(str, env_lst);
// 	// delete_env_var("OLDPWD", &env_lst);
// 	printf("CNT:%d\n", cntenv(env_lst));

// 	printenv(env_lst);

// 	freeenv(env_lst);
// 	return (0);
// }
