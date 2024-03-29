/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 07:01:53 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:43:16 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Converts a string to an integer.
/// @param str The string to convert.
/// @return The converted integer value.
int	ft_atoi(const char *str)
{
	int	num;
	int	i;
	int	neg;

	num = 0;
	i = 0;
	neg = 1;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (num * neg);
}
