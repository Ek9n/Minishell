#include "minishell.h"
// |echo -n " bla"
// | blah
// echo -n " bla"
//  blah
// echo -n" bla"
// -n bla
char	*echo(char *word)
{
	bool	flag;
	flag = false;
	word += 5;
	// printf("HIER\n%s\n", word);
	if (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	else if (*(word + 3) == '\0' && ft_strcmp("-n", word) == 0)
	{
		printf("bla\n");
	}
	if (flag)
		return (ft_savef("%s", word));
	return (ft_savef("%s\n", word));
}
// Minishell>>: "echo hallo du"
// hallo du

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

int	cd(char *dir, char ***env)
{
	char 	*pwd;

	if (dir[2] == ' ')
		dir += 3;
	pwd = ft_strjoin("export OLDPWD=", getpwd());
	if (ft_strcmp(dir, "~") == 0 || ft_strcmp(dir, "cd") == 0)
		dir = ft_strdup(getenv("HOME"));
	if (chdir(dir) != 0) 
    {
        perror("(cd) No valid pathname!");
		free(pwd);
		return (EXIT_FAILURE);
    }
	export(pwd,env);
	free(pwd);
	pwd = ft_strjoin("export PWD=", getpwd());
	export(pwd,env);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	ls(char *dir)
{
	pid_t p = fork();

	if(p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	if (p == 0)
	 {
		char *ls_argv[] = {"ls", dir, NULL};
		execv("/bin/ls", ls_argv);
		perror("execv failed");
		exit(1);
	}
	return 0;
}