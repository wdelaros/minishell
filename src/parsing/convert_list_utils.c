/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:24:05 by rapelcha          #+#    #+#             */
/*   Updated: 2023/09/22 12:43:14 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

// static void	print_node(t_input *list)
// {
// 	while (list)
// 	{
// 		ft_printf("%s	%d\n", list->input, list->token);
// 		list = list->next;
// 	}
// 	ft_printf("\n");
// }

static int	do_need(t_input **ih)
{
	t_input	*temp;
	int		flag;

	temp = (*ih);
	flag = NO;
	while (temp)
	{
		if (temp && temp->next && temp->next->input && temp->token == 0)
		{
			// ft_printf("COMMAND TROUVER: %s	%d\n", temp->input, temp->token);
			while (temp && temp->token != 3)
				temp = temp->next;
			// ft_printf("Commencement de la boucle avec: %s	%d\n", temp->input, temp->token);
			while (temp && temp->next && temp->token != 0 && temp->token != 1
				&& (temp->token != 3 || temp->input[0] != '|')
				&& temp->token != 2)
			{
				// ft_printf("STRING A ETRE TESTE: %s\n", temp->input);
				if (temp && (temp->token == 3
						&& (temp->input[0] == RD_I || temp->input[0] == RD_O)))
					flag = YES;
				temp = temp->next;
			}
			// ft_printf("EST CE QUE JE SUIS UNE OPTION: %s	%d\n", temp->input, temp->token);
			if (temp && (temp->token == 1 || temp->token == 2) && flag == YES)
				return (YES);
		}
		if (temp)
			temp = temp->next;
	}
	ft_printf("J'ai PAS besoin d'etre reorganiser\n");
	return (NO);
}

static int	reorganization(t_input **ih, int where, int command)
{
	t_input	*temp;
	t_input	*res;
	int		count;

	// ft_printf("COMMAND: %d	WHERE: %d\n", command, where);
	// print_node(*ih);
	if (where - command == 1)
		return (NO);
	if (do_need(ih) == NO)
		return (NO);
	temp = (*ih);
	count = 0;
	res = create_node();
	while (temp)
	{
		// ft_printf("COMMAND: %d	WHERE: %d	STR A TRAITER: %s	COUNT: %d\n", command, where, temp->input, count);
		if (count == command && temp->token == 0)
		{
			// ft_printf("COMMAND: %d	WHERE: %d	STR A TRAITER: %s	COUNT: %d\n", command, where, temp->input, count);
			while (temp && (temp->token == 0 || temp->token == 1 || temp->token == 2))
			{
				add_node(&res, temp->token, temp->input);
				temp = temp->next;
				count++;
			}
			// ft_printf("PREMIER: \n");
			// print_node(res);
			while (temp && count++ != where)
				temp = temp->next;
			add_node(&res, temp->token, temp->input);
			// ft_printf("DEUXIEME: \n");
			// print_node(res);
			while (temp && temp->prev && temp->prev->token != 0)
				temp = temp->prev;
			count = command + 1;
			while (temp && (temp->token == 0 || temp->token == 1 || temp->token == 2))
			{
				temp = temp->next;
				count++;
			}
		}
		if (temp->next && count != where)
		{
			// ft_printf("DANS LE IF: \n");
			add_node(&res, temp->token, temp->input);
			// print_node(res);
		}
		count++;
		temp = temp->next;
	}
	free_list(ih);
	*ih = res;
	return (YES);
}

// cat < Makefile -e | cat < Makefile -e | cat -e
// cat -e < Makefile | cat -e < Makefile | cat -e
// echo allo uwu < note.txt coucou | cat

void	put_in_order(t_input **ih)
{
	t_input	*temp;
	int		i;
	int		command;

	if (do_need(ih) == NO)
		return ;
	// ft_printf("J'ai besoin d'etre reorganiser\n");
	temp = (*ih);
	i = 0;
	command = 0;
	while (temp)
	{
		// ft_printf("String a traiter: %s	Token: %d\n", temp->input, temp->token);
		if (temp && temp->next && temp->token == 0)
		{
			while (temp && temp->token != 3)
			{
				i++;
				temp = temp->next;
			}
			// ft_printf("APRES PREMIER WHILE COMMAND: %d	WHERE: %d\n", command, i);
			while (temp && temp->next && temp->token != 0 && temp->token != 1
				&& (temp->token != 3 || temp->input[0] != '|')
				&& temp->token != 2)
			{
				i++;
				temp = temp->next;
			}
			// ft_printf("APRES DEUXIEME WHILE COMMAND: %d	WHERE: %d\n", command, i);
			if (temp && temp->input && (temp->token == 1 || temp->token == 2))
			{
				// ft_printf("Pret a la reorganisation: %s	COMMAND: %d	WHERE: %d\n", temp->input, command, i);
				if (reorganization(ih, i, command) == YES)
				{
					temp = (*ih)->next;
					command = 0;
					i = 0;
				}
				else
					temp = temp->next;
			}
			// ft_printf("Command: %d	Need_to_move: %d\n", command, i);
		}
		else
			temp = temp->next;
		i++;
		command++;
	}
	ft_printf("FINI!\n");
}
