#include <stdio.h>
#include "../libft/libft.h"


void add_env_var(char **str, int *pos)
{
	char    *dup_str;
	char    *dup2_str;
	char    *tmp_str;
	char    *new_str;

	dup_str = ft_strdup(*str);
	dup_str[*pos] = '\0';
	dup2_str = ft_strdup(*str + *pos + 1);
	tmp_str = ft_strjoin(dup_str, "42");
	new_str = ft_strjoin(tmp_str, dup2_str);
	free(*str);
	*str = new_str;
	free(dup_str);
	free(dup2_str);
	free(tmp_str);
}

int main()
{
	char *str = ft_strdup("Hello_$My_Dear, How are you?");

	printf("PreStr:%s\n", str);
	
	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			// printf("blabla at %d\n", i);
			put_env_var(&str, &i);
		}
		i++;
	}
	printf("PostStr:%s\n", str);
	free(str);

	return (0);
}
	// printf("STRING:%s\n", *str);
	// *str = ft_strjoin(dup_str, "blabla");
	// // new_str