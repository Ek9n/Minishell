/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:57:58 by hstein            #+#    #+#             */
/*   Updated: 2024/02/15 15:59:00 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static t_data	*init_data(t_data *data, char **envp, int argc)
{
	if (argc != 1)
	{
		printf("Error: Minishell does not accept any arguments,");
		printf("but nice try ;)\n");
		exit(1);
	}
	data = malloc(sizeof(t_data));
	data->envp = arrdup(envp);
	data -> original_fd_in = dup(STDIN_FILENO);
	data -> original_fd_out = dup(STDOUT_FILENO);
	return (data);
}

static void	run(char *input, t_data	*data)
{
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
			if (data->nodes != NULL)
				executor(data);
		}
		else
			printf("-minishell: %s: Invalid input\n", input);
	}
}

void	reset(t_data *data)
{
	dup2(data->original_fd_in, 0);
	dup2(data->original_fd_out, 1);
	data->last_exit_status = g_exit_status;
	g_exit_status = 0;
}

void	run_shell(t_data *data, char *input)
{
	assign_interactive_signals();
	data->nodes = init_nodes(input, data);
	if (data->nodes != NULL)
		executor(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;
	int		a;

	(void)argv; 
	data = init_data(data, envp, argc);
	while (true)
	{
		assign_signals();
		reset(data);
		input = readline("Minishell>>: ");
		if (input == NULL)
			if (rl_end == 0)
				exit(0);
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (valid_input(input))
				run_shell(data, input);
			else
				printf("-minishell: %s: Invalid input\n", input);
			free_and_close_data(data);
		}
	}
}

/*
"echo bla" should be one work -> split_cmd[0] should be "echo bla" not just "echo"

Minishell>>: cd Repositories/minishell
malloc(): invalid next size (unsorted)
Aborted (core dumped)
Program received signal SIGABRT, Aborted.
__pthread_kill_implementation (no_tid=0, signo=6, threadid=140737350893504) at ./nptl/pthread_kill.c:44
44	./nptl/pthread_kill.c: No such file or directory.
(gdb) TEST STILL!!!!!




*/
//LEAK CHECK COMMAND:
//valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all ./Minishell
/*
LEAK_FIX julius:
in cmp keyword replaced strcmp with strncmp, because of a lot of invalid read errors
*/
/*
LEAKS:
case cat < file
=======
==17522== 135 bytes in 1 blocks are definitely lost in loss record 28 of 72
==17522==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==17522==    by 0x406019: ft_strjoin (ft_strjoin.c:26)
==17522==    by 0x406B09: ft_strjoinfree (in /home/jfoltan/Desktop/42Work/FINAL_MINI/Minishell)
==17522==    by 0x406CA7: ft_strhandler (in /home/jfoltan/Desktop/42Work/FINAL_MINI/Minishell)
==17522==    by 0x406F1A: printtype (in /home/jfoltan/Desktop/42Work/FINAL_MINI/Minishell)
==17522==    by 0x4068CF: ft_writeline (in /home/jfoltan/Desktop/42Work/FINAL_MINI/Minishell)
==17522==    by 0x406A99: ft_savef (in /home/jfoltan/Desktop/42Work/FINAL_MINI/Minishell)
==17522==    by 0x404A2D: expand_vars (expander.c:111)
==17522==    by 0x405675: find_path (executor_utils_3.c:63)
==17522==    by 0x404D96: exec_cmd (executor.c:81)
==17522==    by 0x4051E3: single_command (executor_utils_1.c:66)
==17522==    by 0x404B92: executor (executor.c:25)
==17522== 
=======
==17522== 11 bytes in 1 blocks are definitely lost in loss record 6 of 72
==17522==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==17522==    by 0x406559: ft_strdup (ft_strdup.c:23)
==17522==    by 0x401E96: remove_quotes (lexer_3.c:52)
==17522==    by 0x402122: routine (lexer_3.c:73)
==17522==    by 0x402280: init_nodes (lexer_3.c:104)
==17522==    by 0x401351: run_shell (Main.c:63)
==17522==    by 0x401436: main (Main.c:88)
==17522== 
===== HANNES

*/