/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:49:24 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:15:57 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Compare memory areas.
/// @param s1 Pointer to first memory area.
/// @param s2 Pointer to second memory area.
/// @param n Number of bytes to compare.
/// @return  0 if both memory areas are equal, a negative or positive integer 
/// if s1 is respectively less or greater than s2.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (0);
	str = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (*str == *str2 && --n > 0)
	{
		str++;
		str2++;
	}
	return (*str - *str2);
}
