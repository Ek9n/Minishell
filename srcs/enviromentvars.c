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

int	emptyvar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	printenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!emptyvar(env[i]))
		{
			ft_putstr_fd(env[i], 1);
			printf("\n");
		}
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

void    delete_env_var(char *name, char ***env)
{
    int size = cntenv(*env);
    char    **new_env = 0;
    int i;
    int j;
    new_env = ft_calloc(size + 1, sizeof(char *));
    i = 0;
    j = 0;
    while (env[0][i] != NULL)
    {
        if (ft_strcmp(name, env[0][i]) == 0 && (env[0][i][ft_strlen(name)] == '\0' || env[0][i][ft_strlen(name)] == '='))
        {
            // printf("HLLO:::%c\n", env[0][i][ft_strlen(env[0][i])]);
            // printf("LEN:::%zu\n", ft_strlen(env[0][i]));
            // printf("STR:::%s\n", env[0][i]);
            free(env[0][i]);
        }
        else
        {
            new_env[j] = env[0][i];
            j++;
        }
        i++;
    }
    free(*env);
    *env = new_env;
}

int	valid_var(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (i == 0 && !(ft_isalpha(name[i]) || name[i] == '_'))
		{
			printf("-minishell: export: '%s': not a valid identifier\n" ,name);
			return (0);
		}
		else if (i > 0 && name[i] == '=')
			break ;
		else if (i > 0 && !(ft_isalpha(name[i]) || name[i] == '_' || ft_isdigit(name[i])))
		{
			printf("-minishell: export: '%s': not a valid identifier\n" ,name);
			return (0);
		}
		i++;
	}
	return (1);
}

void	add_env_var(char *name, char ***env)
{
	int		size = cntenv(*env) + 1;
	int		i;
	char	**new_env;

	if (valid_var(name))
	{
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
}

void	purge_arr(char *cmds,char ***env)
{
	char **temp;
	int a;
	a = 0;
	// printf("PURGE:%s\n", cmds);
	temp = ft_split(cmds, '=');
	delete_env_var(temp[0], env);
	while(temp[a])
	{
		free(temp[a]);
		a++;
	}
	free(temp);
}
