/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:34:35 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

char	**ft_sort_params(int nbr_param, char **tabexport)
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

char	*ft_strtrim2(char const *s1, char set)
{
	char	*str;
	size_t	i;
	size_t	index;

	index = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[index] && s1[index] != set)
		index++;
	if (!s1[index])
		index = ft_strlen(s1);
	str = malloc(sizeof(char) * (index + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < index)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

void	print_export(void)
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
			ft_printf("\"%s\"", ft_strchr(export[i], '=') + 1);
		}
		ft_printf("\n");
		i++;
	}
}
