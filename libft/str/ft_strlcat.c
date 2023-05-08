/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:40:45 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:35:09 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Copies a string from src to dst, including null-terminating 
/// character, up to a maximum of dstsize bytes.
/// @param dst The destination buffer to copy the string to.
/// @param src The source string to be copied.
/// @param dstsize The maximum number of bytes to be copied to the destination 
/// buffer.
/// @return The total length of the string that tried to be created, which is 
/// the length of the source string.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	if (!dst || !src)
		return (0);
	len = ft_strlen(dst);
	if (dstsize <= len)
		return (dstsize + ft_strlen(src));
	dstsize -= len + 1;
	while (*src && dstsize-- > 0)
	{
		dst[len++] = *src++;
		dst[len] = 0;
	}
	return (len + ft_strlen(src));
}
