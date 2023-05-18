#include "../../include/minishell.h"

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
		if (struc()->is_child == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		struc()->is_child = 0;
	}
}

int	signal_handler(void)
{
	if (signal(SIGINT, to_be_clearing) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}
