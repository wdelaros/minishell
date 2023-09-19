#include "../../include/minishell.h"

void	print_cell(char	***cell)
{
	int	i;
	int	j;

	i = 0;
	while (cell[i])
	{
		j = 0;
		while (cell[i][j])
		{
			ft_printf("-----------------------------------\n");
			ft_printf("| i = %d                            \n", i);
			ft_printf("| j = %d                            \n", j);
			ft_printf("| cmd : %s            \n", cell[i][j]);
			ft_printf("-----------------------------------\n");
			j++;
		}
		i++;
	}
}

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
		"\x1b[32m""     Rip wagadoo_machine, wagadoo_machine_2, wagadoo_machine_3"\
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
}
