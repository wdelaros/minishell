/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:48:05 by rapelcha          #+#    #+#             */
/*   Updated: 2023/10/11 15:52:40 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

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
