/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:30:31 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:30:32 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putstr_fd(str[i], 0);
			write(1, " ", 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
