/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:27 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/13 15:49:58 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_strlen_until(char *str, int i, char *c)
{
	int	start;
	int	j;
	int	len;

	len = ft_strlen(str);
	j = 0;
	start = i + 1;
	while (c[j])
	{
		i = start;
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
	if (quote == SQ)
	{
		if (input[i] == SQ)
			return (i + 1);
		while (input[i] && input[i] != SQ)
			i++;
	}
	else if (quote == DQ)
	{
		if (input[i] == DQ)
			return (i + 1);
		while (input[i] && input[i] != DQ)
			i++;
	}
	else if (quote == 30)
	{
		if (input[i] == 30)
			return (i + 1);
		while (input[i] && input[i] != 30)
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

void	parsing_is_valid_2(int i, char **str, int size)
{
	if (i > 0 && i < size && (*str)[i] && (*str)[i - 1] && (*str)[i - 1] != 29
		&& ((*str)[i] == RD_O) && ((*str)[i - 1] != RD_O))
		*str = place_group_sep((*str), i - 1, 0);
	if (i < size && (*str)[i] && (*str)[i + 1] && (*str)[i + 1] != 29
		&& ((*str)[i] == RD_I) && ((*str)[i + 1] != RD_I))
		*str = place_group_sep((*str), i, 0);
	if (i < size && (*str)[i] && (*str)[i + 1] && (*str)[i + 1] != 29
		&& ((*str)[i] == RD_O) && ((*str)[i + 1] != RD_O))
		*str = place_group_sep((*str), i, 0);
	if (i < size && (*str)[i] && (*str)[i + 1] && (*str)[i + 1] != 29
		&& ((*str)[i] == PIPE))
		*str = place_group_sep((*str), i, 0);
}
