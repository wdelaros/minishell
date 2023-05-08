/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:45 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:39:22 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Find the last occurrence of a character in a string.
/// @param s  The string to search for the character in.
/// @param c The character to search for.
/// @return This function returns a pointer to the last occurrence of the 
/// character c in the string s. If the character is not found, the function 
/// returns NULL.
char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			str = (char *)s;
		++s;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (str);
}
