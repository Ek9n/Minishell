#include "../includes/minishell.h"

void	sig_handler_C(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	assign_signals(void)
{
	signal(SIGINT, sig_handler_C);
	signal(SIGQUIT, SIG_IGN);
}
void  assign_interactive_signals(void)
{
	signal(SIGINT, assign_interactive_C);
	signal(SIGQUIT, assign_interactive_backslash);
}

void  assign_interactive_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core is dumped,yo)\n",1);
		g_exit_status = 131;
		
	}
}
void assign_interactive_C(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 131;
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}