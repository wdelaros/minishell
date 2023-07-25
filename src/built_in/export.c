#include "../../include/minishell.h"

static void	print_export(void)
{
	int		i;
	int		j;

	i = 0;
	while (struc()->export[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (struc()->export[i][j] != '=' || struc()->export[i][j])
		{
			ft_putchar_fd(struc()->export[i][j], 1);
			j++;
		}
		if (ft_strsearch(struc()->export[i], '='))
		{
			ft_putchar_fd('=', 1);
			ft_printf("\"%s\"\n", ft_strchr(struc()->export[i], '=') + 1);
		}
		i++;
	}
}

int	export(char **content)
{
	if (!content[1])
		print_export();
	else
		;//declare
	return (0);
}
