/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 06:59:01 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:04:38 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Calculates the number of digits in a long integer when represented 
/// in a given base.
/// @param n The long integer to calculate the number of digits for.
/// @param base The base to represent the integer in.
/// @return The number of digits required to represent the integer in the 
/// given base, including a sign character if the integer is negative.
int	ft_intlen(long int n, int base)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > (base - 1))
	{
		n /= base;
		i++;
	}
	return (i);
}
