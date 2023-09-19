/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:27:57 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:27:58 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief This function checks if a given character is a valid ASCII character 
/// or not.
/// @param c The character to be checked.
/// @return Returns 1 if the character is a valid ASCII character, and 0 
/// otherwise.
int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 255) || c == -61 || c == -62)
		return (1);
	else
		return (0);
}
