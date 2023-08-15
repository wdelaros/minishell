#include "../../include/minishell.h"

void	print_cell(char	***cell)
{
	int		j;

	j = 0;
	while (cell[0][j])
	{
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", j);
		ft_printf("| cmd : %s            \n", cell[0][j]);
		ft_printf("-----------------------------------\n");
		j++;
	}
}

void	ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code)
{
	if (code == 127)
		ft_dprintf(2, "minishell: %s: command not found\n", fcmd[0]);
	else if (code == 126)
		ft_dprintf(2, "minishell: %s: Permission denied\n", fcmd[0]);
	else
		ft_dprintf(2, "minishell: %s: exit 1", fcmd[0]);
	ft_free_all_pipe(lcmd, cmd);
	ft_free_null(struc()->path);
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	free(struc()->cmdpath);
	exit (code);
}

int	exit_status(int status)
{
	int	result;

	result = 0;
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_printf("^\\Quit: 3");
		result = (128 + WTERMSIG(status));
	}
	return (result);
}

void	logo(void)
{
	ft_printf("\x1b[35m""%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", \
		" __       __ __          __          __                __ __ ",
		"|  \\     /  \\  \\        |  \\        |  \\              |  \\  \\",
		"| ▓▓\\   /  ▓▓\\▓▓_______  \\▓▓ _______| ▓▓____   ______ | ▓▓ ▓▓",
		"| ▓▓▓\\ /  ▓▓▓  \\       \\|  \\/       \\ ▓▓    \\ /      \\| ▓▓ ▓▓",
		"| ▓▓▓▓\\  ▓▓▓▓ ▓▓ ▓▓▓▓▓▓▓\\ ▓▓  ▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\ ▓▓ ▓▓",
		"| ▓▓\\▓▓ ▓▓ ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓\\▓▓    \\| ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓ ▓▓",
		"| ▓▓ \\▓▓▓| ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓_\\▓▓▓▓▓▓\\ ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓ ▓▓",
		"| ▓▓  \\▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓       ▓▓ ▓▓  | ▓▓\\▓▓     \\ ▓▓ ▓▓",
		" \\▓▓      \\▓▓\\▓▓\\▓▓   \\▓▓\\▓▓\\▓▓▓▓▓▓▓ \\▓▓   \\▓▓ \\▓▓▓▓▓▓▓\\▓▓\\▓▓",
		"\x1b[31m""				     by wdelaros and rapelcha""\x1b[0m");
}
