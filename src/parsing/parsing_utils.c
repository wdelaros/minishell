/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:27 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/10 16:41:56 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_strlen_until(char *str, char *c)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	j = 0;
	while (c[j])
	{
		i = 0;
		while (str[i])
		{
			if ((str[i] == c[j] && i != 0 && len > i))
				len = i;
			i++;
		}
		j++;
	}
	return (len);
}

void	parsing_xfree_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_xfree(str[i]);
		i++;
	}
	ft_xfree(str);
}

int	skip_quote(char *input, int i, int quote)
{
	i++;
	if (quote == 1)
	{
		if (input[i] == SQ)
			return (i + 1);
		while (input[i] && input[i] != SQ)
			i++;
	}
	else if (quote == 2)
	{
		if (input[i] == DQ)
			return (i + 1);
		while (input[i] && input[i] != DQ)
			i++;
	}
	return (i + 1);
}

char	*return_var(char *var, int err, char **env)
{
	char	*var_temp;

	var_temp = NULL;
	if (ft_strncmp(var, "?", 1) == 0)
	{
		var_temp = ft_strdup(var + 1);
		ft_xfree(var);
		var = ft_fstrjoin(ft_itoa(err), var_temp);
	}
	else
	{
		var_temp = ft_fstrjoin(var, "=");
		var = ft_strdup(get_var_parsing(var_temp, env));
	}
	ft_xfree(var_temp);
	return (var);
}

void	parsing_is_valid_2(int i, char **str)
{
	if (i < 1)
		return ;
	if ((*str)[i] && (*str)[i - 1] && (*str)[i - 1] == RD_I
		&& ((*str)[i] != RD_I && (*str)[i] != 29))
		*str = place_group_sep((*str), i - 1, 0);
	else if ((*str)[i] && (*str)[i - 1] && (*str)[i - 1] == RD_O
		&& ((*str)[i] != RD_O && (*str)[i] != 29))
		*str = place_group_sep((*str), i - 1, 0);
	else if ((*str)[i] && (*str)[i - 1] && (*str)[i - 1] == PIPE
		&& ((*str)[i] != PIPE && (*str)[i] != 29))
		*str = place_group_sep((*str), i - 1, 0);
}
