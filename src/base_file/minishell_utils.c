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
	ft_printf("\x1b[35m""%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", \
		" __       __ __          __          __                __ __ ",
		"|  \\     /  \\  \\        |  \\        |  \\              |  \\  \\",
		"| ▓▓\\   /  ▓▓\\▓▓_______  \\▓▓ _______| ▓▓____   ______ | ▓▓ ▓▓",
		"| ▓▓▓\\ /  ▓▓▓  \\       \\|  \\/       \\ ▓▓    \\ /      \\| ▓▓ ▓▓",
		"| ▓▓▓▓\\  ▓▓▓▓ ▓▓ ▓▓▓▓▓▓▓\\ ▓▓  ▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\ ▓▓ ▓▓",
		"| ▓▓\\▓▓ ▓▓ ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓\\▓▓    \\| ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓ ▓▓",
		"| ▓▓ \\▓▓▓| ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓_\\▓▓▓▓▓▓\\ ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓ ▓▓",
		"| ▓▓  \\▓ | ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓       ▓▓ ▓▓  | ▓▓\\▓▓     \\ ▓▓ ▓▓",
		" \\▓▓      \\▓▓\\▓▓\\▓▓   \\▓▓\\▓▓\\▓▓▓▓▓▓▓ \\▓▓   \\▓▓ \\▓▓▓▓▓▓▓\\▓▓\\▓▓",
		"\x1b[31m""				     by wdelaros and rapelcha""\x1b[0m");
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
