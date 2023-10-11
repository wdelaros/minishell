/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:30 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/11 16:55:14 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static char	*ft_parsing_cat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (dest);
}

char	*place_group_sep(char *input, int i, int j)
{
	char	*temp;
	int		k;

	k = 0;
	temp = ft_calloc(ft_strlen(input) + 2, sizeof(char));
	while (input[j])
	{
		if (k == i)
		{
			temp[k++] = input[j++];
			temp[k] = 29;
			k++;
			temp = ft_parsing_cat(temp, &input[j]);
			break ;
		}
		else
		{
			temp[k] = input[j];
			k++;
			j++;
		}
	}
	ft_xfree(input);
	return (temp);
}

static void	parsing_is_valid(int i, char **str)
{
	if ((*str)[i] && (*str)[i + 1] && (*str)[i + 1] == RD_I
		&& ((*str)[i] != RD_I && (*str)[i] != 29))
		*str = place_group_sep((*str), i, 0);
	else if ((*str)[i] && (*str)[i + 1] && (*str)[i + 1] == RD_O
		&& ((*str)[i] != RD_O && (*str)[i] != 29))
		*str = place_group_sep((*str), i, 0);
	else if ((*str)[i] && (*str)[i + 1] && (*str)[i + 1] == PIPE
		&& ((*str)[i] != 31 && (*str)[i] != 29))
		*str = place_group_sep((*str), i, 0);
}

static char	*put_separator(char *input)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(input))
	{
		if (input[i] == SPACE)
			input[i] = 29;
		i++;
	}
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		parsing_is_valid(i, &input);
		parsing_is_valid_2(i, &input);
		i++;
	}
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		if (input[i] == 31)
			input[i] = SPACE;
		i++;
	}
	return (input);
}

char	***string_handler(char *input, char **env, int err_code)
{
	t_input	*input_handler;
	char	***res;

	res = NULL;
	if (input[0] == '\0')
		return (res);
	input_handler = create_node();
	var_handler(&input, env, err_code);
	input = quote_handler(input);
	input = put_separator(input);
	create_list(&input_handler, ft_split(input, 29));
	res = convert_list_to_string(&input_handler, 0);
	free_list(&input_handler);
	ft_xfree(input);
	return (res);
}
