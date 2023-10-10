/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:32 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:49 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	quote_size(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == DQ || input[i] == SQ)
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

int	is_there_after_here(char *input, int i)
{
	while (i > 0)
	{
		if (input[i] == RD_I && input[i - 1] && input[i - 1] == RD_I)
			return (YES);
		if (i > 0)
			i--;
	}
	return (NO);
}

char	*quote_interpreter(char *input, size_t i, size_t j, char c)
{
	char	*res;
	int		max_len;

	// res = ft_calloc(quote_size(input) + 1, sizeof(char));
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (i < ft_strlen(input))
	{
		c = input[i];
		if ((c == DQ || c == SQ) && is_there_after_here(input, i) == YES)
		{
			if (c == DQ)
				max_len = skip_quote(input, i, 2);
			else if (c == SQ)
				max_len = skip_quote(input, i, 1);
			while (max_len > 0 && max_len--)
				res[j++] = input[i++];
			ft_printf("res dedans : %s\n", res);
		}
		if ((c == DQ || c == SQ) && i++)
			while (input[i] && input[i] != c)
				res[j++] = input[i++];
		else
			res[j++] = input[i];
		ft_printf("res: %s\n", res);
		i++;
	}
	free(input);
	return (res);
}

int	is_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == DQ || input[i] == SQ)
			return (YES);
		i++;
	}
	return (NO);
}

char	*quote_handler(char *input)
{
	char	*res;

	res = NULL;
	if (is_quote(input) == YES)
		res = quote_interpreter(input, 0, 0, 'a');
	return (res);
}
