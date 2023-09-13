#include "../../include/built_in.h"

static int	flag_correct(char *flag)
{
	int	i;

	i = 0;
	if (!flag)
		return (NO);
	while (flag[i])
	{
		if (flag[i] && i == 0 && flag[i] != '-')
			return (NO);
		if (flag[i] && i != 0 && flag[i] == '-')
			return (NO);
		if (flag[i] && i != 0 && flag[i] != 'n')
			return (NO);
		i++;
	}
	return (YES);
}

int	echo(char **input)
{
	int	is_flag;
	int	i;

	i = 1;
	if (input[1] && flag_correct(input[1]) == YES)
		is_flag = YES;
	else
		is_flag = NO;
	if (is_flag == YES)
		i = 2;
	while (input[i])
	{
		ft_printf("%s", input[i]);
		if (input[i + 1])
			ft_printf(" ");
		i++;
	}
	if (is_flag == NO)
		write(1, "\n", 1);
	return (0);
}
