#include "../../include/execution.h"

/// @brief create a node for a command
/// @param redir_in the input redirection
/// @param cmd the command
/// @param redir_out the input redirection
/// @return a node that contain the command and the input/output redirection
static t_cmd	*picreate_node(char	**redir_in, char **cmd, char **redir_out)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = cmd;
	node->redir_in = redir_in;
	node->redir_out = redir_out;
	if (cmd == NULL)
		node->good = 0;
	else
		node->good = 1;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

static int ft_here_doc(t_pilist *list, char **str, char *delimiter, char ***cmd)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*line;

	(void)cmd;
	ft_xfree(str[1]);
	str[1] = ft_strdup("allo.txt");
	pid = fork();
	struc()->is_child = 1;
	if (!pid)
	{
		fd = open(str[1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
		line = readline("> ");
		while (strcmp(line, delimiter))
		{
			ft_dprintf(fd, "%s\n", line);
			ft_xfree(line);
			line = readline("> ");
		}
		ft_xfree(line);
		close(fd);
		free(delimiter);
		ft_free_triple_pointer(cmd);
		free_env();
		free(struc()->current_pwd);
		rl_clear_history();
		exit(0);
	}
	list->input = str;
	waitpid(pid, &status, 0);
	if (exit_status(status) == 130)
		return (free(delimiter), 130);
	return (free(delimiter), 0);
}

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

	list.input = NULL;
	list.output = NULL;
	list.command = NULL;
	while (arg && arg[i])
	{
		if (!ft_strcmp(arg[i][0], "<") || !ft_strcmp(arg[i][0], ">") \
		|| !ft_strcmp(arg[i][0], ">>") || !ft_strcmp(arg[i][0], "<<"))
		{
			if (ft_strcmp(arg[i][0], "<<"))
				if (parse_redir(&list, arg, &i))
					break ;
			if (!ft_strcmp(arg[i][0], "<<") && \
			ft_here_doc(&list, arg[i], ft_strdup(arg[i][1]), arg))
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
	(*cmd) = picreate_node(list.input, list.command, list.output);
	return (i);
}

static t_cmd	**finalize_list(t_cmd	**current)
{
	while ((*current) && (*current)->previous)
	{
		if ((*current)->cmd && !strcmp((*current)->cmd[0], "|"))
			struc()->pipenum++;
		else if ((*current)->good == 1)
			e_struc()->number_of_cmd++;
		else
		{
			if (e_struc()->number_of_cmd > 0)
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
	e_struc()->number_of_cmd = 0;
	i = ft_parse_node(arg, &cmd, 0);
	if (i == -1)
	{
		struc()->exit_code = 1;
		return (cmd);
	}
	(*current) = cmd;
	while (arg && arg[i] && arg[i + 1])
	{
		i++;
		i = ft_parse_node(arg, &(*current)->next, i);
		if (i == -1)
		{
			struc()->exit_code = 1;
			return (cmd);
		}
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
	}
	while ((*current) && (*current)->next)
		(*current) = (*current)->next;
	current = finalize_list(current);
	e_struc()->number_of_cmd++;
	cmd = (*current);
	return (cmd);
}
