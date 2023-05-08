/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:04 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:13:03 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief This function converts an integer to a string.
/// @param n The integer to be converted.
/// @return The string representation of the integer. If memory allocation 
/// fails, the function returns NULL.
char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nb;

	nb = n;
	len = ft_intlen(nb, 10);
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (0);
	str[len--] = '\0';
	if (nb == 0)
		str[len--] = 48;
	if (nb < 0)
	{
		str[0] = 45;
		nb *= -1;
	}
	while (nb > 0)
	{
		str[len--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}
