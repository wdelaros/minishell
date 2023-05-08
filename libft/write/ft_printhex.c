/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:18:25 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:30:37 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_convert_to_hex(unsigned int nb, const char format, int fd)
{
	int	a;

	if (format >= 97 && format <= 122)
		a = 87;
	else if (format >= 65 && format <= 90)
		a = 55;
	if (nb > 15)
	{
		ft_convert_to_hex(nb / 16, format, fd);
		ft_convert_to_hex(nb % 16, format, fd);
	}
	else
	{
		if (nb > 9)
			ft_putchar_fd(nb + a, fd);
		else
			ft_putchar_fd(nb + 48, fd);
	}
}

int	ft_printhex(unsigned int nbr, const char format, int fd)
{
	ft_convert_to_hex(nbr, format, fd);
	return (ft_intlen(nbr, 16));
}
