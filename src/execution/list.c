#include "../../include/minishell.h"

t_cmd	*create_node(char	**cmd)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = cmd;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_setnode(char	***arg, t_cmd	**current)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = create_node(arg[i]);
	(*current) = cmd;
	i++;
	while (arg[i])
	{
		(*current)->next = create_node(arg[i]);
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
		i++;
	}
	return (cmd);
}

int	ft_pilesize(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	return (ft_pilesize(cmd->next) + 1);
}
