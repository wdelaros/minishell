/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:29:57 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:29:58 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Concatenates two strings together.
/// @param s1 The first string to be concatenated.
/// @param s2 The second string to be concatenated.
/// @return The concatenated string on success, NULL otherwise.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (0);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	while (s2[k] != '\0')
		str[j++] = s2[k++];
	str[j] = '\0';
	return (str);
}

char	*ft_rstrjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (0);
	while (s2[i] != '\0')
		str[j++] = s2[i++];
	while (s1[k] != '\0')
		str[j++] = s1[k++];
	str[j] = '\0';
	return (str);
}
