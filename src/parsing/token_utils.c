/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:26:00 by rapelcha          #+#    #+#             */
/*   Updated: 2023/09/25 10:28:06 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_separator(char **input, int i)
{
	if (i < 0 || !input[i] || !input[i][0])
		return (NO);
	if (input[i][0] == RD_I || input[i][0] == RD_O || input[i][0] == PIPE)
		return (YES);
	return (NO);
}
