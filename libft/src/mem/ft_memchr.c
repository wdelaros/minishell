/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:23:41 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Locates the first occurrence of a character in a byte string.
/// @param s A pointer to the byte string.
/// @param c The character to be located.
/// @param n The maximum number of bytes to be searched.
/// @return A pointer to the matching byte or NULL if the character does not 
/// occur within the given byte string and search limit.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	while (0 < n--)
		if (*(str++) == (unsigned char)c)
			return (--str);
	return (0);
}
