/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:23:42 by rapelcha          #+#    #+#             */
/*   Updated: 2023/10/11 15:52:21 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	free_list(t_input **input_handler)
{
	while ((*input_handler)->next)
		(*input_handler) = (*input_handler)->next;
	if ((*input_handler))
	{
		while ((*input_handler)->prev != NULL)
		{
			(*input_handler) = (*input_handler)->prev;
			free((*input_handler)->next->input);
			free((*input_handler)->next);
		}
		free((*input_handler)->input);
		free((*input_handler));
	}
}
