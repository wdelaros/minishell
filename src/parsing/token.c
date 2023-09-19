/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:35 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:35:36 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_command(char **input, int i)
{
	if (is_separator(input, i) == YES)
		return (NO);
	if (i == 0)
		return (YES);
	if (i > 0 && input[i - 1][0] == PIPE)
		return (YES);
	if (i > 0 && is_after_red(input, i - 1) == YES)
		return (YES);
	return (NO);
}

int	is_option(char **input, int i)
{
	if (input[i][0] == '-')
		return (YES);
	return (NO);
}

int	is_separator(char **input, int i)
{
	if (i < 0 || !input[i] || !input[i][0])
		return (NO);
	if (input[i][0] == RD_I || input[i][0] == RD_O || input[i][0] == PIPE)
		return (YES);
	return (NO);
}

int	is_after_red(char **input, int i)
{
	if (i <= 0)
		return (NO);
	if (input[i] && input[i - 1])
		if (input[i - 1][0] == RD_I || input[i - 1][0] == RD_O)
			return (YES);
	return (NO);
}

int	is_after_heredoc(char **input, int i)
{
	if (i < 0)
		return (NO);
	if (input[i] && input[i - 1])
		if (input[i - 1][0] && input[i - 1][1])
			if (input[i - 1][0] == RD_I && input[i - 1][1] == RD_I)
				return (YES);
	return (NO);
}
