/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:18:49 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief  Copies a block of memory, handling overlap between source and 
/// destination correctly.
/// @param dst A pointer to the destination memory area.
/// @param src A pointer to the source memory area.
/// @param len The number of bytes to copy.
/// @return A pointer to the destination memory area (dst).
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (!dst || !src)
		return (NULL);
	if (dst != NULL || src != NULL)
	{
		if (dst < src)
		{
			d = dst;
			s = src;
			while (len--)
				*d++ = *s++;
		}
		else
		{
			d = dst + (len - 1);
			s = src + (len - 1);
			while (len--)
				*d-- = *s--;
		}
	}
	return (dst);
}
