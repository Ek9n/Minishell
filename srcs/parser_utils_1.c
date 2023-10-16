#include "parser.h"

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

char	*echo(char *word)
{
	bool	flag;

	flag = false;
	word += 5;
	while (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	if (flag)
		return (ft_savef("%s", word));
	return (ft_savef("%s\n", word));
}

char	*getpwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd() error");
		return (NULL);
	}
	return (buf);
}

int	cd(char *dir)
{
    if (chdir(dir) != 0) 
    {
        perror("(cd) No valid pathname!");
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}