
#include "minishell.h"

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	if (!keyword || !str)
		return (-1);
	len = ft_strlen(keyword);
	if (ft_strlen(str) > 0 && (ft_strcmp(keyword, str) == 0) && (*(str
				+ len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

int	cnt_bytes(char **arr)
{
	int	i;
	int	bytes;

	bytes = 0;
	i = -1;
	while (arr[++i])
		bytes += ft_strlen(arr[i]) + 1;
	bytes += (i + 1) * sizeof(char *);
	return (bytes);
}

int	single_command(t_data *data, int i)
{
	int	b;

	if (data->nodes[i] && data->nodes[i]->split_command[0])
	{
		if (cmp_keyword("echo", data->nodes[i]->command))
			echo(data->nodes[i]);
		else if (cmp_keyword("pwd", data->nodes[i]->split_command[0]))
		{
			data->nodes[i]->output = getpwd();
			printf("%s\n", data->nodes[i]->output);
		}
		else if (cmp_keyword("cd", data->nodes[i]->split_command[0]))
			cd(data->nodes[i], data);
		else if (cmp_keyword("export", data->nodes[i]->split_command[0]))
		{
			b = -1;
			while (data->envp[++b]);
				export(data->nodes[i]->split_command, &data->envp);
			b = -1;
			while (data->envp[++b]);
		}
		else if (cmp_keyword("unset", data->nodes[i]->split_command[0]))
			unset(data->nodes[i]->split_command, &data->envp);
		else if (cmp_keyword("env", data->nodes[i]->split_command[0]))
		{
			printf("single_command//env\n");
			printenv(data->envp);
		}
		else if (cmp_keyword("exit", data->nodes[i]->split_command[0]))
		{
			g_exit_status = 69;
			free_and_close_data(data);
		}
		else if (data->nodes[i]->split_command[0])
			exec_cmd(data->nodes[i]->split_command, data);
	}
	return (0);
}

int	check_for_only_tab_or_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (-1);
}