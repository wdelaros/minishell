/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:29:14 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:29:15 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_realloc(void *old, size_t size, size_t len, size_t new_len)
{
	void	*new;

	if (!old)
		return (NULL);
	new = ft_calloc(size, new_len);
	if (!new)
		return (NULL);
	if (len > new_len)
		ft_memcpy(new, old, size * new_len);
	else
		ft_memcpy(new, old, size * len);
	ft_xfree(old);
	return (new);
}
