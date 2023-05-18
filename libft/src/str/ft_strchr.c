/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:30:57 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/18 13:29:07 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Find the first occurrence of a character in a string
/// @param s The string to search in
/// @param c The character to search for
/// @return A pointer to the located character in the string, or a NULL pointer 
/// if the character is not found.
char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	while (s[n])
		n++;
	while (i++ <= n)
	{
		if (*str++ == (char)c)
			return (--str);
	}
	return (0);
}
