/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:47:35 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief The purpose of this function is to set a block of memory to a 
/// specific value.
/// @param b pointer to the block of memory to be set
/// @param c value to be set
/// @param len number of bytes to be set to the value c
/// @return  A pointer to the memory block b.
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str1;
	size_t			i;

	i = 0;
	str1 = b;
	if (!b)
		return (NULL);
	while (i < len)
		str1[i++] = c;
	return (b);
}
