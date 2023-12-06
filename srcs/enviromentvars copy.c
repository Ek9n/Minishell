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

// char	**delete_env_var(char *name, char **env)
// {
// 	int	size = cntenv(env);

// 	char	**new_env = 0;

// 	new_env = ft_calloc(size, sizeof(char *));
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (ft_strcmp(name, env[i]) != 0)
// 		{
// 			new_env[j] = env[i];
// 			j++;
// 		}
// 		else
// 			free(env[i]);
// 		i++;
// 	}
// 	free(env);
// 	return (new_env);
// }

void	delete_env_var(char *name, char ***env)
{
	int	size = cntenv(*env);
	char	**new_env = 0;
	int	i;
	int	j;

	new_env = ft_calloc(size, sizeof(char *));

	i = 0;
	j = 0;
	while (env[0][i] != NULL)
	{
		if (ft_strcmp(name, env[0][i]) != 0)
		{
			new_env[j] = env[0][i];
			j++;
		}
		else
			free(env[0][i]);
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
			add_env_var(cmds[i], env);
			i++;
		}
	}
	free(cmds);
}

int	main(int argc, char **argv, char **env)
{
	char	**env_lst = arrdup(env);
	// ft_putstr_fd(env_lst[0], 1);
	// printf("CNT:%d\n", cntenv(env_lst));
	// printenv(env_lst);
	// env_lst = delete_env_var("OLDPWD", env_lst);
	// char str[] = "HELLOWORLD";
	char *str;
	str = malloc(50);
	// str = ft_strdup("H=55 JAN=COOL");
	str = ft_strdup("export V1==3=10 HANNES");

	// env_lst = add_env_var(str, env_lst);
	// add_env_var(str, &env_lst);
	export(str, &env_lst);
	export("export", &env_lst);
	// unset("H fafA USER", &env_lst);
	// delete_env_var("VIl H", &env_lst);
	// printf("CNT:%d\n", cntenv(env_lst));

	printenv(env_lst);
	free(str);
	freeenv(env_lst);
	return (0);
}

/*
...
we need two env lists, one clean one with also vars like A=23 and one with also the empty vars like from export like just B
or we just dont show them all with env...when they have no value
....task done with second option...
input checker für export und unset
*/