/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 06:46:56 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	**ft_free_null(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static size_t	ft_cols(char const *s, char c)
{
	size_t	i;
	size_t	nb_cols;

	nb_cols = 0;
	if (!s[0])
		return (0);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_cols++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_cols++;
	return (nb_cols);
}

static void	ft_row(char **row, size_t *len, char c)
{
	size_t	i;

	*row += *len;
	*len = 0;
	i = 0;
	while (**row && **row == c)
		(*row)++;
	while ((*row)[i])
	{
		if ((*row)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

/// @brief Splits a string into an array of substrings based on a delimiter.This
/// function splits a string into an array of substrings based on a specified 
/// delimiter character.s Pointer to the string to be split.
/// @param c The delimiter character that is used to separate the substrings.
/// @return  A pointer to an array of strings, where each element is a 
///substring of the original string. If the allocation fails, it returns NULL.
char	**ft_split(char const *s, char c)
{
	char	**str;
	char	*row;
	size_t	i;
	size_t	len;
	size_t	cols;

	if (!s)
		return (0);
	cols = ft_cols(s, c);
	str = ft_calloc(sizeof(char *), (cols + 1));
	if (!str)
		return (0);
	row = (char *)s;
	i = 0;
	len = 0;
	while (i < cols)
	{
		ft_row(&row, &len, c);
		str[i] = ft_calloc(sizeof(char), (len + 1));
		if (!str[i])
			return (ft_free_null(str));
		ft_strlcpy(str[i], row, len + 1);
		i++;
	}
	return (str);
}

/// @brief Splits a string into an array of strings, where each string contains 
/// one character from the input string.
/// @param lines The input string to be split.
/// @return An array of strings, where each string contains one character 
/// from the input string, or NULL if memory allocation fails
char	**ft_split_char(const char *lines)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_strlen(lines) + 1, sizeof(char *));
	if (!str)
		return (0);
	while (lines[i])
	{
		str[i] = ft_calloc(2, sizeof(char));
		if (!str[i])
			return (ft_free_null(str));
		str[i][0] = lines[i];
		i++;
	}
	return (str);
}
