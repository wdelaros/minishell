/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:32 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/25 10:54:57 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	quote_size(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
			{
				i++;
				count++;
			}
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*quote_interpreter(char *input, size_t i)
{
	size_t	j;
	char	*res;

	j = 0;
	res = ft_calloc(quote_size(input) + 1, sizeof(char));
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE)
		{
			i++;
			while (input[i] && input[i] != SINGLE_QUOTE)
				res[j++] = input[i++];
		}
		else if (input[i] == DOUBLE_QUOTE)
		{
			i++;
			while (input[i] && input[i] != DOUBLE_QUOTE)
				res[j++] = input[i++];
		}
		else
			res[j++] = input[i];
		i++;
	}
	ft_xfree(input);
	return (res);
}

int	is_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
			return (YES);
		i++;
	}
	return (NO);
}

void	quote_handler(t_input **input)
{
	t_input	*temp;

	temp = *input;
	while (temp->next)
	{
		if (is_quote(temp->input) == YES && temp->token != 5)
			temp->input = quote_interpreter(temp->input, 0);
		temp = temp->next;
	}
}
