#include "../../include/minishell.h"

static char	**ft_sort_params(int nbr_param, char **tabexport)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < nbr_param)
	{
		j = i + 1;
		while (j < nbr_param)
		{
			if (ft_strcmp(tabexport[j], tabexport[i]) < 0)
			{
				temp = tabexport[i];
				tabexport[i] = tabexport[j];
				tabexport[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tabexport);
}

static void	print_export(void)
{
	char	**export;
	int		i;
	int		j;

	i = 0;
	export = struc()->export;
	export = ft_sort_params(ft_strlen_double(export), export);
	while (export[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (export[i][j] != '=' && export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			j++;
		}
		if (ft_strsearch(export[i], '='))
		{
			ft_putchar_fd('=', 1);
			ft_printf("\"%s\"\n", ft_strchr(export[i], '=') + 1);
		}
		i++;
	}
}

static void	parse_export(char	*content)
{
	char	**export;
	int		i;
	int		j;

	i = 0;
	export = struc()->export;
	while ()
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
