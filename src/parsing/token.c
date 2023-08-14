#include "../../include/parsing.h"

int	is_command(char **input, int i)
{
	if (i == 0)
		return (YES);
	if (is_separator(input, i - 1) == YES)
		return (YES);
	return (NO);
}

int	is_option(char **input, int i)
{
	if (input[i][0] == '-')
		return (YES);
	return (NO);
}

int	is_separator(char **input, int i)
{
	if (input[i][0] == RED_IN || input[i][0] == RED_OUT || input[i][0] == PIPE)
		return (YES);
	return (NO);
}
