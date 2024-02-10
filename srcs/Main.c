/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/10 17:02:56 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;
// int cd_flag = 0;

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
	t_data	*data;
	char	*input;
	int		a;

	(void)argc; //have to protect arguments
	(void)argv; 
	data = init_data(data, envp);
	while (true)
	{
		assign_signals();
		dup2(data->original_fd_in, 0);
		dup2(data->original_fd_out, 1);
		data->last_exit_status = g_exit_status;
		g_exit_status = 0;
		input = readline("Minishell>>: ");
		if (input == NULL)
			if (rl_end == 0)
				exit(0);
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (valid_input(input))
			{
				assign_interactive_signals();
				data->nodes = init_nodes(input, data);
	// printf("INITmain:%s\n", data->nodes[0]->command);
				// print_nodes(data->nodes);
				// printf("MAIN:%s\n", data->nodes[0]->split_command[1]);
				if (data->nodes != NULL)
					Executor(data);
			}
			else
				printf("-minishell: %s: Invalid input\n", input);
		}
			 free_and_close_data(data);
		// printf("After routine. (in main)\n");
	}
}

/* TODO

Minishell>>: cat < file2 > file ls
put error for bs 
echo -n is FUCKED
when baa is ls -l its empty in executor.



Different output than bash.. but may not important: // JULIUS
	Minishell>>: cat file3 | wv
	/snap/bin/wv : No such file or directory

only tabs are still interpreted as commands // JULIUS FIXED

Minishell>>: ./home/jfoltan/Desktop/test/a.out 
command not found should be no such file or directory // JULIUS FIXED

debug info in heredoc, maybe add variable expansion? //JULIUS FIXED

cat ctrlc exit code is 131 instead of 130 //JULIUS FIXED

exit with n as argument //JULIUS I guess fixed

----
semi-FIXED for now... removed the last split in getfd for it.. may it makes new problems
	Minishell>>: export baa="env | grep PWD"
		executerEnvVars1:47|
	-minishell: export: '|': not a valid identifier
		executerEnvVars2:49|
----
###########
JULIUS WEDNESDAY:

Minishell>>: echo "cunt" > file3
Minishell>>: echo -n "cunt" > file3
two different outputs, one with -n doestn output to file. 
echo cunt >file3 | grep cunt infinite loop ? FIXED
--
Minishell>>: export baa="env | grep $USER > file3"
Minishell>>: $baa //quite broken
---


When I comment out the last split in getfds: 

 env | grep $USER >file3 no longer works, basically all redirections without spaces: "cat<file2>file3>file4"... all break. 




echoi cunt


#################
=====================
when I remove 


============
----------------------------------------------

only spaces provide pwd??? //HANNES FIXED

exho h 			g with tabs //HANNES FIXED

Minishell>>: echo bla | wc < file3
      2       4      22		//HANNES FIXED

Minishell>>: cat < file2 > file3 | wc < file3
0 0 0 						//HANNES FIXED
// Minishell>>: cat f1 > f2 | wc < f2
// 1 1 3
// Minishell>>: echo bla | wc < f3
// 1 1 5
// Minishell>>: cat f1 > f2 | wc < f2
// 1 1 3
// Minishell>>: 
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ cat f1 > f2 | wc < f2
// 1 1 3
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ echo bla | wc < f3
// 1 1 5
// hstein@c4b1c1:~/Repositories/Minishell_NewMerged$ 


Minishell>>: cat
^\Quit: (core is dumped,yo)
Minishell>>: echo $?
130 should be 131 //fixed


=======
Minishell>>: export baa=15
executerEnvVars1:47|
executerEnvVars2:48|
Minishell>>: $baa
/snap/bin/15 : No such file or directory
Minishell>>: export baa= 15
executerEnvVars1:48|
-minishell: export: '15': not a valid identifier
executerEnvVars2:48|
Minishell>>: export 3baa=15
executerEnvVars1:48|
-minishell: export: '3baa=15': not a valid identifier
executerEnvVars2:48|
Minishell>>: $baa
zsh: segmentation fault (core dumped)  ./Minishell
its because of empty variable FIXED

======

Minishell>>: file 3 << HERE
> 
> 
> ds
3: cannot open `3' (No such file or directory) // julius
*/