#include "../../include/minishell.h"

t_cmd	*create_node(char	**cmd, char	**redir_in, char	**redir_out)
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

int	ft_in_out_node(char	***arg, t_cmd	**cmd, int i)
{
	int	j;

	while (!ft_strcmp(arg[i + 1][0], "<"))
		i++;
	if (arg[i + 2] && (!ft_strcmp(arg[i + 2][0], ">") || \
	!ft_strcmp(arg[i + 2][0], ">>")))
	{
		j = 2;
		while (arg[i + j + 1] && (!ft_strcmp(arg[i + j + 1][0], ">") \
		|| !ft_strcmp(arg[i + j + 1][0], ">>")))
			j++;
		(*cmd) = create_node(arg[i + 1], arg[i], arg[i + j]);
		i += j;
	}
	else
	{
		(*cmd) = create_node(arg[i + 1], arg[i], NULL);
		i++;
	}
	return (i);
}

int	ft_parse_node(char	***arg, t_cmd	**cmd, int i)
{
	int		j;

	if (!ft_strcmp(arg[i][0], "<"))
		i = ft_in_out_node(arg, cmd, i);
	else if (arg[i + 1] && (!ft_strcmp(arg[i + 1][0], ">") || \
	!ft_strcmp(arg[i + 1][0], ">>")))
	{
		j = 1;
		while (arg[i + j + 1] && (!ft_strcmp(arg[i + j + 1][0], ">") \
		|| !ft_strcmp(arg[i + j + 1][0], ">>")))
			j++;
		(*cmd) = create_node(arg[i], NULL, arg[i + j]);
		i += j;
	}
	else
		(*cmd) = create_node(arg[i], NULL, NULL);
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

int	ft_pilesize(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	return (ft_pilesize(cmd->next) + 1);
}
