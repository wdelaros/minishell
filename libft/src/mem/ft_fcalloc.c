/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:23:49 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief free and calloc memory for an array of elements and initializes them
/// 0.
/// @param ptr the pointer to realloc.
/// @param count the number of elements to be reallocated.
/// @param size the size of each element in bytes.
/// @return A pointer to the reallocated memory, or NULL if reallocation fails.
void	*ft_fcalloc(void *ptr, size_t count, size_t size)
{
	if (ptr)
		free(ptr);
	ptr = ft_calloc(size, count);
	if (!ptr)
		return (0);
	return (ptr);
}
