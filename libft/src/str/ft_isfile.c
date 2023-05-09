/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 07:29:16 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Determines if a file has a valid extension
/// @param file The name of the file to check
/// @return An integer representing the type of file: 1 for .txt files, 
/// 2 for .fdf files, 3 for .ber files, 4 for .ans files, and 
/// 0 for all other files or if file is NULL.
int	ft_isfile(char *file)
{
	if (!file)
		return (0);
	else if (!ft_strncmp(ft_strnstr(file, ".txt", 5), ".txt", 5) && \
			!ft_strncmp(ft_strrchr(file, 46), ".txt", 5))
		return (1);
	else if (!ft_strncmp(ft_strnstr(file, ".fdf", 5), ".fdf", 5) && \
	!ft_strncmp(ft_strrchr(file, 46), ".fdf", 5))
		return (2);
	else if (!ft_strncmp(ft_strnstr(file, ".ber", 5), ".ber", 5) && \
	!ft_strncmp(ft_strrchr(file, 46), ".ber", 5))
		return (3);
	else if (!ft_strncmp(ft_strnstr(file, ".ans", 5), ".ans", 5) && \
	!ft_strncmp(ft_strrchr(file, 46), ".ans", 5))
		return (4);
	return (0);
}
