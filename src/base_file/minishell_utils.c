#include "../../minishell.h"

void	print_cell(char	**cell)
{
	int		i;

	i = 0;
	while (cell[i])
	{
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", i);
		ft_printf("| cmd : %s            \n", cell[i]);
		ft_printf("-----------------------------------\n");
		i++;
	}
}
