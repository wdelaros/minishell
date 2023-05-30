#include "../../include/minishell.h"

void	print_cell(char	***cell)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cell[0][j])
	{
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", i);
		ft_printf("| cmd : %s            \n", cell[0][j]);
		ft_printf("| number of pipe : %d            \n", struc()->pipenum);
		ft_printf("| number of cmd : %d            \n", struc()->number_of_cmd);
		ft_printf("-----------------------------------\n");
		j++;
	}
}
