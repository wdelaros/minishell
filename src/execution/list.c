#include "../../include/minishell.h"

/// @brief create a node for a command
/// @param redir_in the input redirection
/// @param cmd the command
/// @param redir_out the input redirection
/// @return a node that contain the command and the input/output redirection
static t_cmd	*picreate_node(char	**redir_in, char	**cmd, char	**redir_out)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = cmd;
	node->redir_in = redir_in;
	node->redir_out = redir_out;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

static int	ft_parse_node(char	***arg, t_cmd	**cmd, int i)
{
	char	**input;
	char	**command;
	char	**output;

	input = NULL;
	output = NULL;
	command = NULL;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i][0], "<"))
			input = arg[i];
		else if (!ft_strcmp(arg[i][0], ">") || !ft_strcmp(arg[i][0], ">>"))
			output = arg[i];
		else
			command = arg[i];
		if (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
		ft_strcmp(arg[i + 1][0], "|")))
			i++;
		else
			break ;
	}
	(*cmd) = picreate_node(input, command, output);
	return (i + 1);
}

t_cmd	*ft_setnode(char	***arg, t_cmd	**current)
{
	t_cmd	*cmd;
	int		i;

	i = ft_parse_node(arg, &cmd, 0);
	(*current) = cmd;
	while (arg[i])
	{
		i = ft_parse_node(arg, &(*current)->next, i);
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
	}
	return (cmd);
}
