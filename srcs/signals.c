/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:43:52 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/12 20:08:28 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	assign_signals(void)
{
	signal(SIGINT, sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

void	assign_interactive_signals(void)
{
	signal(SIGINT, assign_interactive_c);
	signal(SIGQUIT, assign_interactive_backslash);
}

void	assign_interactive_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core is dumped,yo)\n", 1);
		g_exit_status = 131;
	}
}

void	assign_interactive_c(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 131;
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}
