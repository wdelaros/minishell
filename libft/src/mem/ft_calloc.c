/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:07:25 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/// @brief Allocates memory for an array of elements and initializes them to 0.
/// @param count the number of elements to be allocated.
/// @param size the size of each element in bytes.
/// @return A pointer to the allocated memory, or NULL if allocation fails.
void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = malloc((size * count));
	if (!new)
		return (0);
	ft_bzero(new, count * size);
	return (new);
}
