/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:10:09 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:41:44 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Extracts a portion of a string starting from a specified index and 
/// having a specified length
/// @param s The input string.
/// @param start The starting index of the substring to be extracted.
/// @param len The maximum length of the substring to be extracted.
/// @return A newly allocated substring, or NULL if the allocation fails or 
/// the start index is greater than the length of the string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		count;
	size_t	i;

	i = 0;
	count = start;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
		while (s[count++] && i < len)
			i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	if (start >= ft_strlen(s))
		return (str);
	ft_strlcpy(str, &s[start], i + 1);
	return (str);
}
