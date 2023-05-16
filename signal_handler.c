/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:59:59 by rapelcha          #+#    #+#             */
/*   Updated: 2023/05/16 16:49:42 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	to_be_clearing(int sig)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (struc()->is_child == 0)
		term.c_lflag &= ~ECHOCTL;
	else if (struc()->is_child == 1)
		term.c_lflag = DEFAULT_ECHO_TERM;
	tcsetattr(0, TCSANOW, &term);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (struc()->is_child == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	signal_handler(void)
{
	if (signal(SIGINT, to_be_clearing) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, to_be_clearing) == SIG_ERR)
		return (1);
	return (0);
}
