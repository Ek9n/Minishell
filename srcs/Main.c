/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/06 18:33:25 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int g_exit_status = 0;

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
		printf("slash");
	fflush(0);
}
t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	data -> envp = arrdup(envp);
	data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	act;
	t_data				*data;
	char				*input;

	(void)argc;
	(void)argv; 
	data = init_data(data, envp); 
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	while (true)
	{
		
		dup2(data->original_fd_in, 0);
		dup2(data->original_fd_out, 1);
		input = readline("Minishell>>: ");
		if (input)
			add_history(input); // history works
		if (input && input[0] != '\0')
		{
		data->INstruct = init_word_stack(input, data->INstruct,data);
		if (data->INstruct != NULL)
			Executor(data);
		}
		ft_putnbr_fd(g_exit_status, 1);
		write(1, "\n", 1);
		unlink(".heredoc"); // have to move this  somewhere else,and protect it.
		printf("After routine (in main)!\n");
	}
}

 /* 
 TODO:
 always put spaces between tokens //hannes
 quotes and double quotes //hannes
 EXIT SIGNALS //julius
 $? exit code + executor and piperino waitpid // both 
 piperino use our functions, if theres that (execve and inbuilt) /hannes
 clear history in main when exit status is bad. //julius
  ====
  handle input of && and || -invalid input //IN PROGRESS 
  edge case doc: 
  unset home and cd , cd doesnt care, it should fail and exit. 
  cd doesnt update exit code.. we need to pass the data strcut to cd.
  ====
  
  FROM EVAL SHEET: (https://42evals.com/Cursus/minishell) password for website is CVb3d2023
  simple command with absolute path (ls /bin) - FIXED
  after execve failure child doesnt terminate. - FIXED
  only spaces in command line it exits lol tabs too // Hannes
  echo -n prints -n, and with input doesnt work correctly
  $? handle that, it should be 127 if command not found
  ctrl + c doesnt work
  handle /
  handle d
  double quotes dont work... echo "cat lol.c | cat > lol.c"
  echo '$USER' prints '$USER' / echo is completely bad..
  relative path ? 
  unsetting path doesnt prevent command from working. 
  
  ///////////////////////////////////////////////////
	cat < file
  		Program received signal SIGSEGV, Segmentation fault.
		0x00007ffff7dc13fe in __GI___libc_free (mem=0x21) at ./malloc/malloc.c:3368
		3368	./malloc/malloc.c: No such file or directory.

  */