#include "../../libft.h"

void	ft_print_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putstr_fd(str[i], 0);
			write(1, " ", 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
