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

char *expand_env(char *str, t_data *data)
{
    int a;
    int i = 0;
    int c = 0;
    int dollar_index;
    char *temp;
    char *temp2;
printf("(expand_env) str:%s\n", str);
    if ((dollar_index = find_char_from_index(str, '$', 0)) == -1)
        return (str);
printf("(expand_env) dollar_idx:%d\n", dollar_index);
    temp = dollar_baby(str);
printf("(expand_env) temp:%s\n", temp);
    a = find_var(temp,data->envp);
    if (a != -1)
    {

        temp2 = ft_calloc(ft_strlen(str) - ft_strlen(temp) + ft_strllen(data->envp[a],find_char_from_index(data->envp[a],'=',0)) + 1, sizeof(char));
        while (i < dollar_index)
        {
            temp2[i] = str[i];
            i++;
        }
        while (data->envp[a][c] != '=')
            c++;
        c++;
        while (data->envp[a][c])
        {
            temp2[i++] = data->envp[a][c++];
        }
        int j = dollar_index + ft_strlen(temp) + 1; // +1 to skip the $ character
        while (str[j])
        {
            temp2[i++] = str[j++];
        }
printf("(expand_env)11 strout:%s\n", temp2);
    }
    else
    {

        temp2 = ft_calloc(ft_strllen(str,find_char_from_index(str, '$', 0)) + 1, sizeof(char));
        while (str[i] != '$' && str[i])
        {
            temp2[i] = str[i];
            i++;
        }
printf("(expand_env)22 strout:%s\n", temp2);
    }
    free(temp);
	if (ft_strcmp(temp2, "?") == 0)
		temp2 = ft_itoa(data->last_exit_status);
printf("(expand_env) strout:%s\n", temp2);

    return (temp2);
}