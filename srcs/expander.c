#include "../includes/minishell.h"

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
	if (ft_strcmp(temp2, "?") == 0)
		temp2 = ft_strdup("ZEROBIATCH");
    return temp2;
}