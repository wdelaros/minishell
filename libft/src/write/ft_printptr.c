/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:54:02 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	ft_convert_ptr_to_hex(uintptr_t nb, int *len, int fd)
{
	if (nb > 15)
	{
		ft_convert_ptr_to_hex(nb / 16, len, fd);
		ft_convert_ptr_to_hex(nb % 16, len++, fd);
	}
	else
	{
		if (nb > 9)
			(*len) += ft_printchar(nb + 87, fd);
		else
			(*len) += ft_printchar(nb + 48, fd);
	}
}

int	ft_printptr(uintptr_t ptr, int fd)
{
	int	len;

	len = 2;
	ft_printstr("0x", fd);
	ft_convert_ptr_to_hex(ptr, &len, fd);
	return (len);
}
