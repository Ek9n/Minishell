#include "minishell.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;
	
	if (!s1 || !s2)
		return (-1);
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

void 	print_nodes(t_words **nodes)
{
	int i;
	int a;
	i = 0;
	a = 0;
	while (nodes[i])
	{
		printf("command at pos %i: %s\n", i,nodes[i]->command);
		while (nodes[i]->split_command[a])
		{
			printf("split_command at node %i, pos %i: %s\n", i,a,nodes[i]->split_command[a]);
			a++;
		}
		i++;
	}
	
}

// char *ft_join(char **arr)
// {
//     int 	i;
// 	char 	*str;

// 	str = NULL;
//     // size_t current_length = 0;
// 	printf("foin_in:%s\n", arr[0]);
// 	printf("foin_in:%s\n", arr[1]);
// 	printf("foin_in:%s\n", arr[2]);

// 	i = -1;
// 	while (arr[++i])
// 	{
// 		// if (arr[i][0] == '\0')
// 		// 	str = ft_strjoinfree(str, " ");

// 		str = ft_strjoinfree(str, arr[i]);
// 		// if (arr[i + 1] != NULL)
// 		// 	str = ft_strjoinfree(str, " ");
// 	}

// 	printf("foin_out:%s\n", str);

//     return (str);
// }

char *ft_join(char **arr)
{
    int i = 0;
    int total_length = 0;
    size_t current_length = 0;
	// printf("foin_in:%s\n", arr[0]);
	// printf("foin_in:%s\n", arr[1]);
	// printf("foin_in:%s\n", arr[2]);
    while (arr[i] != NULL)
    {
        total_length += ft_strlen(arr[i]);
        i++;
    }
	char *str = (char *)malloc(total_length * sizeof(char) + 1);
    if (!str)
        return NULL;

    str[0] = '\0';
    i = 0;
    while (arr[i] != NULL)
    {
		if (arr[i][0] != 6)
		{
		if (arr[i][0] == '\0')
			arr[i] = ft_strdup(" ");
        current_length += ft_strlcat(str, arr[i], total_length + i + 1);
        // if (arr[i + 1] && arr[i + 1][0] != '\0')
        if (arr[i + 1] && arr[i + 1][0] != '\0')
            current_length += ft_strlcat(str, " ", total_length + i + 1);
		}
		i++;
    }
	// printf("foin_out:%s\n", str);

    return str;
}