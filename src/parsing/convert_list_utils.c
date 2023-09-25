/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:24:05 by rapelcha          #+#    #+#             */
/*   Updated: 2023/09/25 13:20:56 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	do_need(t_input **ih, int flag)
{
	t_input	*tp;

	tp = (*ih);
	while (tp)
	{
		if (tp && tp->next && tp->next->input && tp->token == 0)
		{
			while (tp && tp->token != 3)
				tp = tp->next;
			while (tp && tp->next && tp->token != 0 && tp->token != 1 && (tp->\
				token != 3 || tp->input[0] != '|') && tp->token != 2)
			{
				if (tp && (tp->token == 3
						&& (tp->input[0] == RD_I || tp->input[0] == RD_O)))
					flag = YES;
				tp = tp->next;
			}
			if (tp && (tp->token == 1 || tp->token == 2) && flag == YES)
				return (YES);
		}
		if (tp)
			tp = tp->next;
	}
	return (NO);
}

static void	do_while(t_input **temp, t_input **res, t_reorg *reorg)
{
	while ((*temp) && ((*temp)->token == 0 || (*temp)->token == 1 
			|| (*temp)->token == 2))
	{
		add_node(res, (*temp)->token, (*temp)->input);
		(*temp) = (*temp)->next;
		reorg->count++;
	}
	while ((*temp) && reorg->count++ != reorg->where)
		(*temp) = (*temp)->next;
	add_node(res, (*temp)->token, (*temp)->input);
	while ((*temp) && (*temp)->prev && (*temp)->prev->token != 0)
		(*temp) = (*temp)->prev;
	reorg->count = reorg->command + 1;
	while ((*temp) && ((*temp)->token == 0 || (*temp)->token == 1 
			|| (*temp)->token == 2))
	{
		(*temp) = (*temp)->next;
		reorg->count++;
	}
}

static int	reorganization(t_input **ih, t_reorg *reorg)
{
	t_input	*temp;
	t_input	*res;

	if (reorg->where - reorg->command == 1)
		return (NO);
	if (do_need(ih, 0) == NO)
		return (NO);
	temp = (*ih);
	reorg->count = 0;
	res = create_node();
	while (temp)
	{
		if (reorg->count == reorg->command && temp->token == 0)
			do_while(&temp, &res, reorg);
		if (temp->next && reorg->count != reorg->where)
			add_node(&res, temp->token, temp->input);
		reorg->count++;
		temp = temp->next;
	}
	free_list(ih);
	*ih = res;
	return (YES);
}

static void	do_the_while(t_input **temp, t_input **ih, t_reorg *reorg)
{
	while ((*temp) && (*temp)->token != 3)
	{
		reorg->where++;
		(*temp) = (*temp)->next;
	}
	while ((*temp) && (*temp)->next && (*temp)->token != 0
		&& (*temp)->token != 1 && ((*temp)->token != 3
			|| (*temp)->input[0] != '|') && (*temp)->token != 2)
	{
		reorg->where++;
		(*temp) = (*temp)->next;
	}
	if ((*temp) && (*temp)->input && ((*temp)->token == 1
			|| (*temp)->token == 2))
	{
		if (reorganization(ih, reorg) == YES)
		{
			(*temp) = (*ih)->next;
			reorg->command = 0;
			reorg->where = 0;
		}
		else
			(*temp) = (*temp)->next;
	}
}

void	put_in_order(t_input **ih)
{
	t_input	*temp;
	t_reorg	reorg;

	if (do_need(ih, 0) == NO)
		return ;
	temp = (*ih);
	reorg.where = 0;
	reorg.command = 0;
	while (temp)
	{
		if (temp && temp->next && temp->token == 0)
			do_the_while(&temp, ih, &reorg);
		else
			temp = temp->next;
		reorg.where++;
		reorg.command++;
	}
}
