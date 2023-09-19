#include "../../include/execution.h"

static int	parse_redir(t_pilist *list, char ***arg, int *i)
{
	if (!ft_strcmp(arg[*i][0], "<"))
	{
		if (access(arg[*i][1], F_OK | R_OK))
		{
			*i = ft_perror(arg, *i, list);
			return (1);
		}
		list->input = arg[*i];
	}
	else if (!ft_strcmp(arg[*i][0], ">") || !ft_strcmp(arg[*i][0], ">>"))
	{
		if (!ft_strcmp(arg[*i][0], ">"))
			list->fd = open(arg[*i][1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
		else if (!ft_strcmp(arg[*i][0], ">>"))
			list->fd = open(arg[*i][1], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
		if (list->fd == -1)
		{
			*i = ft_perror(arg, *i, list);
			return (1);
		}
		close(list->fd);
		list->output = arg[*i];
	}
	return (0);
}

static int	ft_parse_node(char ***arg, t_cmd **cmd, int i)
{
	t_pilist	list;

	list = list_null();
	while (arg && arg[i])
	{
		if (!ft_strcmp(arg[i][0], "<") || !ft_strcmp(arg[i][0], ">") \
		|| !ft_strcmp(arg[i][0], ">>") || !ft_strcmp(arg[i][0], "<<"))
		{
			if (ft_strcmp(arg[i][0], "<<"))
				if (parse_redir(&list, arg, &i))
					break ;
			if (!ft_strcmp(arg[i][0], "<<") && \
			ft_here_doc(&list, arg[i], cmd, arg))
				return (-1);
		}
		else
			list.command = arg[i];
		if (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
		ft_strcmp(arg[i + 1][0], "|")))
			i++;
		else
			break ;
	}
	(*cmd) = finish_node((*cmd), list.input, list.command, list.output);
	return (i);
}

static t_cmd	**finalize_list(t_cmd	**current)
{
	while ((*current) && (*current)->previous)
	{
		if ((*current)->cmd && !strcmp((*current)->cmd[0], "|"))
			struc()->pipenum++;
		else if ((*current)->good == 1)
			ex_struc()->number_of_cmd++;
		else
		{
			if (ex_struc()->number_of_cmd > 0)
			{
				while ((*current)->previous)
					(*current) = (*current)->previous;
				while ((*current)->good)
				{
					(*current) = (*current)->next;
					free((*current)->previous);
					(*current)->previous = NULL;
				}
			}
			return (current);
		}
		(*current) = (*current)->previous;
	}
	return (current);
}

t_cmd	*ft_setnode(char	***arg, t_cmd	**current)
{
	t_cmd	*cmd;
	int		i;

	struc()->pipenum = 0;
	ex_struc()->number_of_cmd = 0;
	cmd = picreate_node();
	i = ft_parse_node(arg, &cmd, 0);
	(*current) = cmd;
	if (i == -1)
		return (cmd);
	while (arg && arg[i] && arg[i + 1])
	{
		(*current)->next = picreate_node();
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
		i++;
		i = ft_parse_node(arg, current, i);
		if (i == -1)
			return (cmd);
	}
	current = finalize_list(current);
	ex_struc()->number_of_cmd++;
	cmd = (*current);
	return (cmd);
}
