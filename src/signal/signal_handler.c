/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:43 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:35:44 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	to_be_clearing(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	struc()->exit_code = 1;
}

static void	normal_behavior(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 0);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

static void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		struc()->exit_code = 1;
		ft_dprintf(STDERR_FILENO, "\n");
		close(STDIN_FILENO);
	}
}

void	signal_handler_child(int heredoc)
{
	if (heredoc == YES)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	signal_handler(int sleep, int interactive)
{
	if (interactive == YES)
	{
		signal(SIGINT, to_be_clearing);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sleep == YES)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, normal_behavior);
		signal(SIGQUIT, normal_behavior);
	}
	return (0);
}
