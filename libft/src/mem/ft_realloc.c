/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:02 by rapelcha          #+#    #+#             */
/*   Updated: 2023/05/16 15:40:13 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_realloc(void *old, size_t count, size_t size, size_t new_size)
{
	void	*new;

	if (!old)
		return (NULL);
	new = ft_calloc(count, new_size);
	if (!new)
		return (NULL);
	if (size > new_size)
		ft_memcpy(new, old, count * new_size);
	else
		ft_memcpy(new, old, count * size);
	ft_xfree(old);
	return (new);
}
