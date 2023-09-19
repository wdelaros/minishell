/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:30:14 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:30:15 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Checks if the character is inside the string.
/// @param string The string that is being checked.
/// @param character The character to find.
/// @return Returns 1 if the character is found inside the string and is not
/// '\0', and 0 otherwise.
int	ft_strsearch(char *string, char character)
{
	int	index;

	index = 0;
	if (character == '\0')
		return (0);
	while (string[index])
	{
		if (string[index] == character && string[index] != '\0')
		{
			return (1);
		}
		index++;
	}
	return (0);
}
