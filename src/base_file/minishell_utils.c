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
		result = (128 + WTERMSIG(status));
	return (result);
}
