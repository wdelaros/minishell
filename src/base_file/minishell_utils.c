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
