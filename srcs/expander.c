#include "../includes/minishell.h"


int find_var(char *str, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
        if (ft_strcmp(str, envp[i]) == 0 && (envp[i][ft_strlen(str)] == '\0' || envp[i][ft_strlen(str)] == '='))
			return (i);
		i++;
	}
	return (-1);
}

char *put_var(char **str, int dollar_pos, char **envp)
{
	char *tmp;
	tmp = malloc(ft_strlen(*str));

	int	i;
	int	j;

	i = dollar_pos;
	j = 0;

	while ((ft_isalpha(str[0][i]) || str[0][i] == '_') && str[0][i] != 26)
	{
		tmp[j] = str[0][i];
		j++;
		// if (ft_isalnum(str[0][i]) && str[0][i] != '$')
		i++;
	}
	tmp[j] = '\0';
	int var_idx = find_var(tmp, envp);
	free(tmp);
	if (var_idx != -1)
	{
		tmp = envp[var_idx];
		// printf("VARinENVP:%s\n", envp[var_idx]);
		
	}
	else
		tmp = NULL;
	return (tmp);
}

int	cnt_var(char **str, int dollar_pos)
{
	int	i;
	int	j;

	i = dollar_pos + 1;
	j = 0;

	while ((ft_isalpha(str[0][i]) || str[0][i] == '_') && str[0][i] != 26)
	{
		j++;
		i++;
	}
	return (j);
}

int	expand_vars(char **input, int i, t_data *data)
{
	char	*left_str = NULL;
	char	*tmp_var = NULL;
	char	*mid_str = NULL;
	char	*right_str = NULL;
	char	*new_str;
	int		cnt;

	left_str = ft_strdup(input[0]);
	left_str[i] = '\0';
	tmp_var = put_var(input, i + 1, data->envp);

	if (tmp_var != NULL)
	{
		cnt = ft_strchr(tmp_var, '=') - tmp_var + 1;
		mid_str = ft_strdup(ft_strchr(tmp_var, '=') + 1);
	}
	else
	{
		cnt = cnt_var(input, i);
		// printf("CNT:%d\n", cnt);
		// printf("HIER:%c\n", input[0][i + 1]);
		if (cnt == 0 && input[0][i + 1] == '?')
		{
			mid_str = ft_itoa(data->last_exit_status);
			cnt++;
		}
		else if (cnt == 0)
			mid_str = ft_strdup("$");
		else
			mid_str = ft_strdup("");
		cnt++;
	}
	right_str = &input[0][i + cnt];
	new_str = ft_savef("%s%s%s", left_str, mid_str, right_str);
	free(left_str);
	free(mid_str);
	free(input[0]);
	input[0] = new_str;

	// printf("CNT:%d\n", cnt);
	// printf("VAR:%s\n", ft_strchr(tmp_var, '=') + 1);
	// printf("right:%s\n", right_str);
	// printf("line:%s\n", input[0]);
		// printf("left_str|%s|\n", left_str);
		// printf("tmp_var|%s|\n", tmp_var);
		// printf("input + cnt|%s|\n", &input[0][i + cnt]);
		// printf("INPUT|%s|\n", input[0]);
		// printf("OUTPUT|%s|\n", new_str);
		// printf("___len|%d|\n", ft_strlen(new_str));
	return (0);
}
