/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:19 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 16:31:21 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	logo(void)
{
	ft_printf("\x1b[35m""%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", \
		"  __       __ __          __          __                __ __ ",
		" |  \\     /  \\  \\        |  \\        |  \\              |  \\  \\",
		" | ▓▓\\   /  ▓▓\\▓▓_______  \\▓▓ _______| ▓▓____   ______ | ▓▓ ▓▓",
		" | ▓▓▓\\ /  ▓▓▓  \\       \\|  \\/       \\ ▓▓    \\ /      \\| ▓▓ ▓▓",
		" | ▓▓▓▓\\  ▓▓▓▓ ▓▓ ▓▓▓▓▓▓▓\\ ▓▓  ▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\ ▓▓ ▓▓",
		" | ▓▓\\▓▓ ▓▓ ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓\\▓▓    \\| ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓ ▓▓",
		" | ▓▓ \\▓▓▓| ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓_\\▓▓▓▓▓▓\\ ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓ ▓▓",
		" | ▓▓  \\▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓       ▓▓ ▓▓  | ▓▓\\▓▓     \\ ▓▓ ▓▓",
		"  \\▓▓      \\▓▓\\▓▓\\▓▓   \\▓▓\\▓▓\\▓▓▓▓▓▓▓ \\▓▓   \\▓▓ \\▓▓▓▓▓▓▓\\▓▓\\▓▓",
		"\x1b[32m"\
		"     Rip wagadoo_machine, wagadoo_machine_2, wagadoo_machine_3"\
		"\x1b[0m",
		"\x1b[31m""					by wdelaros & rapelcha""\x1b[0m");
}

char	*ft_prompt_line(void)
{
	char	*line;

	line = NULL;
	if (struc()->current_pwd && ft_strlen(struc()->current_pwd) > 1)
		line = ft_fstrjoin(ft_strjoin(GRN"", \
		ft_strrchr(struc()->current_pwd, '/') + 1), WHT" minishell> ");
	else if (struc()->current_pwd && ft_strlen(struc()->current_pwd) == 1)
		line = ft_fstrjoin(ft_strjoin(GRN"", \
		ft_strrchr(struc()->current_pwd, '/')), WHT" minishell> ");
	return (line);
}

void	ft_error(int code)
{
	struc()->exit_code = 258;
	if (code == 1)
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (code == 2)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `newline'\n");
	else if (code == 3)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `quote'\n");
	else if (code == 4)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `<'\n");
	else if (code == 5)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `>'\n");
	else if (code == 6)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `<<'\n");
	else if (code == 7)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `>>'\n");
}
