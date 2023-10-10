/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:35:14 by rapelcha          #+#    #+#             */
/*   Updated: 2023/10/09 12:20:30 by rapelcha         ###   ########.fr       */
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
				|| str[i + 1] == '?' || str[i + 1] == DQ || str[i + 1] == SQ))
			return (YES);
		i++;
	}
	return (NO);
}
