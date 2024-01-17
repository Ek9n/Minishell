/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:40:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/01/17 11:51:11 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	data->envp = arrdup(envp);
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
		if (input[0] != '\0')
		{
			replace_spaces_in_quotes(input);
			expand_env
			printf("%s\n",input);
			
			//data->INstruct = init_word_stack(input);
			//clean_words(data->INstruct);
			//print_words(data->INstruct);
			//if (data->INstruct != NULL)
				//Executor(data);
			
		}
		unlink(".heredoc");
		// printf("After routine (in main)!\n");
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
  only spaces in command line it exits lol tabs too // Hannes
  echo -n prints -n, and with input doesnt work correctly
  $? handle that, it should be 127 if command not found
  double quotes dont work... echo "cat lol.c | cat > lol.c"
  echo '$USER' prints '$USER' / echo is completely bad..
  relative path ? 
  unsetting path doesnt prevent command from working. 
  
  ///////////////////////////////////////////////////
	cat < file
  		Program received signal SIGSEGV, Segmentation fault.
		0x00007ffff7dc13fe in __GI___libc_free (mem=0x21) at ./malloc/malloc.c:3368
		3368	./malloc/malloc.c: No such file or directory.
	segfault is sorted, it was a mistake in my freeing and exit function. 
	cat is failing because there are double spaces, when spaces already exist, split gets a little oofed.


	Tests:
Minishell>>: ec"ho" "bla" bla
Syntax is wrong, Sunny.Syntax is wrong, Sunny.
Return not expected. Must be an execve error.
free(): invalid next size (fast)
Return not expected. Must be an execve error.
free(): invalid next size (fast)
free(): invalid pointer
Aborted (core dumped)

Julius:
Please fix it when the line is like cmd asd"sadad"adsdas << lexer cuts the rest away

Minishell>>: echo "bal"dasd
Syntax is wrong, Sunny.InExecutor:echo "bal"
Minishell>>: ech"ho" bla
Syntax is wrong, Sunny.InExecutor:ech"ho"
Minishell>>: ed"f asd "dadas
Return not expected. Must be an execve error.
InExecutor:
Segmentation fault (core dumped)


May we need to check if the cmds are existing allrdy.. and not do it by execve:
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/hstein/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
PATH=/home/hstein/bin:/home/hstein/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
FRESH_STRUCTURE

A=IAMVAR
ec"ho $Abla"dasd|   blu"b" >file

#sub spaces in quotes with unprintables
ec"ho@$Abla"dasd|   blu"b" >file

#Split by Pipes
a) ec"ho@$Abla"dasd /b)    blu"b" >file

#Extend spaces (for redirections)
a) ec"ho@$Abla"dasd /b)    blu"b"  > file

#Clean Spaces
a) ec"ho@$Abla"dasd /b) blu"b" > file

#Split by spaces
a) //a.1) ec"ho@$Abla"dasd /b) //b.1) blu"b" //b.2) > //b.3) file

#bring back the spaces
a) //a.1) ec"ho $Abla"dasd /b) //b.1) blu"b" //b.2) > //b.3) file

#Add Vars
a) //a.1) ec"ho IAMVARbla"dasd /b) //b.1) blu"b" //b.2) > //b.3) file

#Get rid of quotes
a) //a.1) echo IAMVARbladasd /b) //b.1) blub //b.2) > //b.3) file


// A=BLA
// hstein@c4b6c1:~/Repositories/minishell$ bash
// hstein@c4b6c1:~/Repositories/minishell$ echo bla$A
// blaBLA
// hstein@c4b6c1:~/Repositories/minishell$ echo bla$Adum
// bla
// hstein@c4b6c1:~/Repositories/minishell$ echo bl"a$Ad"um
// blaum
// hstein@c4b6c1:~/Repositories/minishell$ echo $Abla
// 

*/