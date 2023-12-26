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

void	add_env_var(char *name, char ***env)
{
	int		size = cntenv(*env) + 1; //phne +1 segfault... why?
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
	ft_putnbr_fd(i, 1);
	free(*env);
	*env = new_env;
}


void	unset(char *str, char ***env)
{
	char	**cmds;
	int		i;

	cmds = ft_split(str, ' ');
	i = 0;
	if (cmds[1] == NULL)
		printf("something!\n");
	while (cmds[i])
	{
		delete_env_var(cmds[i], env);
		i++;
	}
}


int	correct_input(char **cmds)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 1;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if ((cmds[i][0] >= '0' && cmds[i][0] <= '9') || !((cmds[i][j] >= 'a' && cmds[i][j] <= 'z') || \
				(cmds[i][j] >= 'A' && cmds[i][j] <= 'Z') || \
				cmds[i][j] == '_' || (cmds[i][j] >= '0' && cmds[i][j] <= '9')) && !flag)
			{
				printf("%c\n", cmds[i][j]);
				printf("minishell: export: `%s': not a valid identifier\n" ,cmds[i]);
				return (0);
			}
			j++;
			if (cmds[i][j] == '=')
				flag = 1;
		}
		i++;
	}
	return (1);
}
void	purge_arr(char *cmds,char ***env)
{
	char **temp;
	int a;
	a = 0;

			temp = ft_split(cmds, '=');
			delete_env_var(temp[0], env);
			while(temp[a])
			{
				free(temp[a]);
				a++;
			}
			free(temp);
}
void	export(char *str, char ***env)
{
	char	**cmds;

	int		i;

	cmds = ft_split(str, ' ');
	if (!correct_input(cmds))
	{
		free(cmds);
		return ;
	}
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
	free(cmds);
}
int	find_char_from_index(char *str, char c, int index)
{
	int	i;

	i = index;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char *dollar_baby(char *str)
{
	char	*temp;
	int		i;

	i = find_char_from_index(str, '$', 0) + 1;
	temp = ft_substr(str, i,find_char_from_index(str, ' ', i) - i);
	return(temp);
}
int find_var(char *str, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(str, envp[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
int	ft_strllen(char *str,int i)
{
	while (str[i])
		i++;
	return (i);
}
char *expand_env(char *str, char **env)
{
    int a;
    int i = 0;
    int c = 0;
    int dollar_index;
    char *temp;
    char *temp2;

    if ((dollar_index = find_char_from_index(str, '$', 0)) == -1)
        return (str);
    temp = dollar_baby(str);
    a = find_var(temp,env);
    if (a != -1)
    {
        temp2 = ft_calloc(ft_strlen(str) - ft_strlen(temp) + ft_strllen(env[a],find_char_from_index(env[a],'=',0)) + 1, sizeof(char));
        while (i < dollar_index)
        {
            temp2[i] = str[i];
            i++;
        }
        while (env[a][c] != '=')
            c++;
        c++;
        while (env[a][c])
        {
            temp2[i++] = env[a][c++];
        }
        int j = dollar_index + ft_strlen(temp) + 1; // +1 to skip the $ character
        while (str[j])
        {
            temp2[i++] = str[j++];
        }
    }
    else
    {
        temp2 = ft_calloc(ft_strllen(str,find_char_from_index(str, '$', 0)) + 1, sizeof(char));
        while (str[i] != '$' && str[i])
        {
            temp2[i] = str[i];
            i++;
        }
    }
    free(temp);
    return temp2;
}