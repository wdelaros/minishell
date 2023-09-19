#include "../../include/execution.h"

//"/tmp/.HeReDoC00"
static int	ft_here_doc(t_pilist *list, char **str, t_cmd **current, \
char ***cmd)
{
	t_heredoc	hd;
	int			fd;
	char		*delimiter;
	char		*line;
	int			flag;

	flag = YES;
	delimiter = ft_strdup(str[1]);
	if (is_quote(delimiter) == YES)
	{
		delimiter = quote_interpreter(delimiter, 0);
		flag = NO;
	}
	ft_xfree(str[1]);
	str[1] = heredoc_file();
	hd.pid = fork();
	if (!hd.pid)
	{
		rl_clear_history();
		signal_handler_child(YES);
		fd = open(str[1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
		line = readline("> ");
		if (!line)
			exit(struc()->exit_code);
		while (ft_strcmp(line, delimiter))
		{
			if (flag == YES)
				line = mini_parsing(line, struc()->envp, struc()->exit_code);
			fstat(fd, &hd.sfd);
			stat(str[1], &hd.sfile);
			if (hd.sfd.st_mtime == hd.sfile.st_mtime)
				ft_dprintf(fd, "%s\n", line);
			else
			{
				printf("wagadoo_machine\n");
				struc()->exit_code = 1;
				break ;
			}
			ft_xfree(line);
			line = readline("> ");
			if (!line)
				exit(struc()->exit_code);
		}
		ft_xfree(line);
		close(fd);
		free(delimiter);
		ft_free_triple_pointer(cmd);
		free_env();
		free(struc()->current_pwd);
		if ((*current))
		{
			while ((*current)->previous != NULL)
			{
				(*current) = (*current)->previous;
				free((*current)->next);
			}
			free((*current));
		}
		exit(struc()->exit_code);
	}
	signal_handler(YES, NO);
	waitpid(hd.pid, &hd.status, 0);
	signal_handler(0, 0);
	list->input = str;
	struc()->exit_code = exit_status(hd.status);
	if (struc()->exit_code == 1 && !access(str[1], F_OK))
		unlink(str[1]);
	return (free(delimiter), struc()->exit_code);
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
	if (i == -1)
		return (cmd);
	(*current) = cmd;
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
