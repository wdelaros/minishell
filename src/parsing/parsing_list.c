/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:24 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/25 07:46:22 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_input	*create_node(void)
{
	t_input	*temp;

	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->token = -1;
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}

void	add_node(t_input **input, int id, char *str)
{
	t_input	*current;

	if (*input == NULL)
	{
		(*input) = create_node();
		return ;
	}
	current = (*input);
	while (current->next != NULL)
		current = current->next;
	current->next = create_node();
	if (!current->next)
		return ;
	current->next->prev = current;
	current->token = id;
	current->input = ft_strdup(str);
}

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

void	create_list(t_input **list, char **input)
{
	t_input	*temp;
	int		i;

	temp = *list;
	i = 0;
	while (input[i])
	{
		if (is_command(input, i, temp) == YES)
			add_node(&temp, COMMAND, input[i]);
		else if (is_option(input, i) == YES)
			add_node(&temp, OPTION, input[i]);
		else if (is_separator(input, i) == YES)
			add_node(&temp, SEPARATOR, input[i]);
		else if (is_after_heredoc(input, i) == YES)
			add_node(&temp, 5, input[i]);
		else if (is_after_red(input, i) == YES)
			add_node(&temp, 4, input[i]);
		else
			add_node(&temp, ARGUMENT, input[i]);
		i++;
		temp = temp->next;
	}
	parsing_xfree_double(input);
}
