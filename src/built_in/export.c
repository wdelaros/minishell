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
		while (struc()->export[i][j] != '=' && struc()->export[i][j])
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
	int	i;

	i = 1;
	struc()->exit_code = 0;
	if (!content[i])
		print_export();
	else
	{
		while (content[i])
		{
			if ((!ft_isalpha(content[i][0]) && content[i][0] != '_') || \
			ft_strsearch(content[i], 32))
			{
				ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", \
				content[i]);
				struc()->exit_code = 1;
				i++;
				continue ;
			}
			i++;
		}
	}
	return (struc()->exit_code);
}
