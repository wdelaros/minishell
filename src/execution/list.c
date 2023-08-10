#include "../../include/execution.h"

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

static int	ft_perror(char ***arg, int i, t_pilist	*list)
{
	perror(arg[i][1]);
	while (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
	ft_strcmp(arg[i + 1][0], "|")))
		i++;
	list->input = NULL;
	list->output = NULL;
	list->command = NULL;
	e_struc()->number_of_cmd--;
	if (e_struc()->number_of_cmd > 0)
	{
		while (ft_strcmp(arg[i][0], "|") && arg[i + 1])
			i++;
		struc()->pipenum--;
	}
	struc()->exit_code = 1;
	return (i + 1);
}

static int	ft_parse_node(char	***arg, t_cmd	**cmd, int i)
{
	t_pilist	list;

	list.input = NULL;
	list.output = NULL;
	list.command = NULL;
	while (arg && arg[i])
	{
		if (!ft_strcmp(arg[i][0], "<"))
		{
			if (access(arg[i][1], F_OK | R_OK))
			{
				i = ft_perror(arg, i, &list);
				continue ;
			}
			list.input = arg[i];
		}
		else if (!ft_strcmp(arg[i][0], ">") || !ft_strcmp(arg[i][0], ">>"))
		{
			if (!ft_strcmp(arg[i][0], ">"))
				list.fd = open(arg[i][1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
			else if (!ft_strcmp(arg[i][0], ">>"))
				list.fd = open(arg[i][1], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
			if (list.fd == -1)
			{
				i = ft_perror(arg, i, &list);
				continue ;
			}
			close(list.fd);
			list.output = arg[i];
		}
		else
			list.command = arg[i];
		if (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
		ft_strcmp(arg[i + 1][0], "|")))
			i++;
		else
			break ;
	}
	(*cmd) = picreate_node(list.input, list.command, list.output);
	return (i);
}

t_cmd	*ft_setnode(char	***arg, t_cmd	**current)
{
	t_cmd	*cmd;
	int		i;

	i = ft_parse_node(arg, &cmd, 0);
	(*current) = cmd;
	while (arg && arg[i] && arg[i + 1])
	{
		i++;
		i = ft_parse_node(arg, &(*current)->next, i);
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
	}
	return (cmd);
}
