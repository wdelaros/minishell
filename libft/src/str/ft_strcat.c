/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:29:42 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:29:43 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Copies a string from src to dst, including null-terminating 
/// character
/// @param dst The destination buffer to copy the string to.
/// @param src The source string to be copied.
/// @return The total length of the string that tried to be created, which is 
/// the length of the source string.
size_t	ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (i);
}
