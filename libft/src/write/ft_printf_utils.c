/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:12:32 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_printchar(int c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_printnbr(int nbr, int fd)
{
	ft_putnbr_fd(nbr, fd);
	return (ft_intlen(nbr, 10));
}

int	ft_printstr(char *str, int fd)
{
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	ft_printunnbr(unsigned int nbr, int fd)
{
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
	return (ft_intlen(nbr, 10));
}
