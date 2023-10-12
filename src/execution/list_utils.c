/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:01 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 07:39:41 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/// @brief create a node
/// @return a node that contain the command and the input/output redirection
t_cmd	*picreate_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

/// @brief finish a node for a command
/// @param node the node to finsh
/// @param redir_in the input redirection
/// @param cmd the command
/// @param redir_out the input redirection
/// @return a node that contain the command and the input/output redirection
t_cmd	*finish_node(t_cmd *node, char	**redir_in, char **cmd, \
char **redir_out)
{
	node->cmd = cmd;
	node->redir_in = redir_in;
	node->redir_out = redir_out;
	if (cmd == NULL)
		node->good = 0;
	else
		node->good = 1;
	return (node);
}

t_pilist	list_null(void)
{
	t_pilist	list;

	list.input = NULL;
	list.output = NULL;
	list.command = NULL;
	return (list);
}

int	ft_perror(char ***arg, int i, t_pilist	*list)
{
	ft_dprintf(2, "Minishell: %s: ", arg[i][1]);
	perror(arg[i][1]);
	while (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
	ft_strcmp(arg[i + 1][0], "|")))
		i++;
	if (ft_strcmp(arg[i][0], "|") && !arg[i + 1])
		struc()->exit_code = 1;
	list->input = NULL;
	list->command = NULL;
	list->output = NULL;
	return (i);
}
