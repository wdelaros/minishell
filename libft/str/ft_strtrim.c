/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 06:44:16 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:41:15 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_s1_in_set(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

/// @brief Allocates a new string by trimming leading and trailing characters 
/// from a given string.
/// @param s1 The string to be trimmed.
/// @param set The set of characters to be trimmed.
/// @return The newly allocated string, or NULL if allocation failed.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_s1_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_s1_in_set(s1[end - 1], set))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
