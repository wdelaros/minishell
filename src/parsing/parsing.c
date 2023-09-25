/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:30 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/25 09:51:41 by wdelaros         ###   ########.fr       */
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

static char	*place_group_sep(char *input, int i, int j)
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

static char	*put_separator(char *input)
{
	int	i;

	i = 0;
	while (i <= (int)ft_strlen(input) && input[i])
	{
		if (input[i] == DOUBLE_QUOTE)
			i += ft_strlen_until(&input[i], "\"") + 1;
		else if (input[i] == SINGLE_QUOTE)
			i += ft_strlen_until(&input[i], "\'") + 1;
		else if (input[i + 1] && ((input[i + 1] == RD_I || input[i + 1] == RD_O
					|| input[i + 1] == PIPE))
			&& input[i] != SPACE && input[i] != 29 && input[i] != RD_O
			&& input[i] != RD_I)
			input = place_group_sep(input, i, 0);
		else if (i > 0 && input[i - 1] && ((input[i - 1] == RD_I
					|| input[i - 1] == RD_O || input[i - 1] == PIPE))
			&& input[i] != SPACE && input[i] != 29 && input[i] != RD_O
			&& input[i] != RD_I)
			input = place_group_sep(input, i - 1, 0);
		else if (input[i] == SPACE)
			input[i] = 29;
		i++;
	}
	return (input);
}

// static void	print_node(t_input *list)
// {
// 	while (list)
// 	{
// 		ft_printf("%s	%d\n", list->input, list->token);
// 		list = list->next;
// 	}
// 	ft_printf("\n");
// }

char	***string_handler(char *input, char **env, int err_code)
{
	t_input	*input_handler;
	char	***res;
	char	*cpy_input;

	res = NULL;
	if (input[0] == '\0')
		return (res);
	cpy_input = ft_strdup(input);
	input_handler = create_node();
	cpy_input = put_separator(cpy_input);
	create_list(&input_handler, ft_split(cpy_input, 29));
	var_handler(&input_handler, env, err_code);
	quote_handler(&input_handler);
	res = convert_list_to_string(&input_handler, 0);
	int	i;
	int	j;

	i = 0;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			ft_printf("-----------------------------------\n");
			ft_printf("| i = %d                            \n", i);
			ft_printf("| j = %d                            \n", j);
			ft_printf("| cmd : %s            \n", res[i][j]);
			ft_printf("-----------------------------------\n");
			j++;
		}
		i++;
	}
	free_list(&input_handler);
	ft_xfree(cpy_input);
	return (res);
}
