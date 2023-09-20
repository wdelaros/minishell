/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:35:14 by rapelcha          #+#    #+#             */
/*   Updated: 2023/09/20 14:13:03 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	valid_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalnum(str[i + 1]) == YES
				|| str[i + 1] == '?'))
			return (YES);
		else if (str[i] == '$' && !str[i + 1])
			return (YES);
		i++;
	}
	return (NO);
}
