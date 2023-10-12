/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:55 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 16:06:00 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	exit_heredoc(t_cmd **current, t_heredoc hd, char ***cmd, \
int fd)
{
	ft_xfree(hd.line);
	close(fd);
	free(hd.delimiter);
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

static void	prompt_heredoc(t_cmd **current, t_heredoc hd, char **str, \
char ***cmd)
{
	signal_handler_child(YES);
	hd.fd = open(str[1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	hd.line = readline("> ");
	if (!hd.line)
		exit_heredoc(current, hd, cmd, hd.fd);
	while (ft_strcmp(hd.line, hd.delimiter))
	{
		if (hd.flag == YES)
			hd.line = mini_parsing(hd.line, struc()->envp, struc()->exit_code);
		fstat(hd.fd, &hd.sfd);
		stat(str[1], &hd.sfile);
		if (hd.sfd.st_mtime == hd.sfile.st_mtime)
			ft_dprintf(hd.fd, "%s\n", hd.line);
		else
		{
			ft_dprintf(2, "rip wagadoo_machine\n");
			struc()->exit_code = 1;
			break ;
		}
		ft_xfree(hd.line);
		hd.line = readline("> ");
		if (!hd.line)
			exit_heredoc(current, hd, cmd, hd.fd);
	}
	exit_heredoc(current, hd, cmd, hd.fd);
}

static char	*quote_interpreter_hd(char *input, size_t i)
{
	size_t	j;
	char	*res;

	j = 0;
	res = ft_calloc(quote_size(input) + 1, sizeof(char));
	while (input[i])
	{
		if (input[i] == SQ)
		{
			i++;
			while (input[i] && input[i] != SQ)
				res[j++] = input[i++];
		}
		else if (input[i] == DQ)
		{
			i++;
			while (input[i] && input[i] != DQ)
				res[j++] = input[i++];
		}
		else
			res[j++] = input[i];
		i++;
	}
	ft_xfree(input);
	return (res);
}

int	ft_here_doc(t_pilist *list, char **str, t_cmd **current, char ***cmd)
{
	t_heredoc	hd;

	hd.flag = YES;
	hd.delimiter = ft_strdup(str[1]);
	if (is_quote(hd.delimiter) == YES)
	{
		hd.delimiter = quote_interpreter_hd(hd.delimiter, 0);
		hd.flag = NO;
	}
	ft_xfree(str[1]);
	str[1] = heredoc_file();
	hd.pid = fork();
	if (!hd.pid)
	{
		rl_clear_history();
		prompt_heredoc(current, hd, str, cmd);
	}
	signal_handler(YES, NO);
	waitpid(hd.pid, &hd.status, 0);
	signal_handler(0, 0);
	list->input = str;
	struc()->exit_code = exit_status(hd.status);
	if (struc()->exit_code == 1 && !access(str[1], F_OK))
		unlink(str[1]);
	return (free(hd.delimiter), struc()->exit_code);
}
