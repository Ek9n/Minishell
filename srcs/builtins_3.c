void do_export(char **split_cmds, char ***env)
{
	int		i;

	i = 1;
	while (split_cmds[i])
	{
		purge_arr(split_cmds[i], env);
		add_env_var(split_cmds[i], env);
		i++;
	}
}