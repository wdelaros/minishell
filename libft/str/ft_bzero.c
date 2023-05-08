/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:44:06 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 08:42:05 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Sets a block of memory to zero.
/// @param s a pointer to the memory block to be set to zero.
/// @param len the number of bytes to be set to zero.
void	ft_bzero(void *s, size_t len)
{
	if (!s)
		return ;
	ft_memset(s, 0, len);
}
