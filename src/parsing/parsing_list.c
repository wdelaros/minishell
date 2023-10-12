/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:24 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 10:56:59 by rapelcha         ###   ########.fr       */
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

static void	do_cleaning(t_input **list)
{
	t_input	*temp;
	int		i;
	int		size;
	char	*res;
	int		j;

	temp = *list;
	while (temp)
	{
		i = 0;
		j = 0;
		res = ft_calloc(ft_strlen(temp->input) + 1, sizeof(char));
		size = (int)ft_strlen(temp->input);
		while (i < size)
		{
			if (temp->input[i] != 30)
				res[j++] = temp->input[i];
			i++;
		}
		free(temp->input);
		temp->input = ft_strdup(res);
		free(res);
		temp = temp->next;
	}
}

static void	do_deep_cleaning(t_input **list, int i, int flag, int size)
{
	t_input	*temp;

	temp = *list;
	while (temp)
	{
		i = 0;
		flag = NO;
		size = ft_strlen(temp->input);
		while (i < size)
		{
			if (temp->input[i] == '\0' && temp->input[i] != 30)
			{
				flag = YES;
				break ;
			}
			i++;
		}
		i = -1;
		while (++i < size && flag == YES)
			temp->input[i] = '\0';
		temp = temp->next;
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
		else if (is_separator(input, i) == YES)
			add_node(&temp, SEPARATOR, input[i]);
		else if (is_after_heredoc(input, i) == YES)
			add_node(&temp, 5, input[i]);
		else if (is_after_red(input, i) == YES)
			add_node(&temp, 4, input[i]);
		else if (is_option(input, i) == YES)
			add_node(&temp, OPTION, input[i]);
		else
			add_node(&temp, ARGUMENT, input[i]);
		i++;
		temp = temp->next;
	}
	do_deep_cleaning(list, 0, NO, 0);
	do_cleaning(list);
	parsing_xfree_double(input);
}
