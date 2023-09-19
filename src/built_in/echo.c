/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:27 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:34:28 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

static int	flag_correct(char *flag)
{
	int	i;

	i = 0;
	if (!flag[0])
		return (NO);
	while (flag[i])
	{
		if (flag[i] && i == 0 && flag[i] != '-')
			return (NO);
		if (flag[i] && i != 0 && flag[i] == '-')
			return (NO);
		if (flag[i] && i != 0 && flag[i] != 'n')
			return (NO);
		i++;
	}
	return (YES);
}

int	echo(char **input)
{
	int	is_flag;
	int	i;

	i = 1;
	is_flag = NO;
	while (input[i] && flag_correct(input[i]) == YES)
	{
		is_flag = YES;
		i++;
	}
	while (input[i])
	{
		ft_printf("%s", input[i]);
		if (input[i + 1])
			ft_printf(" ");
		i++;
	}
	if (is_flag == NO)
		write(1, "\n", 1);
	return (0);
}
