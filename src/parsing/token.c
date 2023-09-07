#include "../../include/parsing.h"

int	is_command(char **input, int i)
{
	printf ("ASGIDF: %c\n", *input[i]);
	if (i == 0 && is_separator(input, i) == NO)
		return (YES);
	if (i > 0 && input[i - 1][0] == PIPE)
		return (YES);
	if (i > 0 && is_after_red(input, i - 1) == YES)
		return (YES);
	printf ("NON JE NE SUIS PAS UNE COMMAND\n");
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
	if (i < 0 || !input[i] || !input[i][0])
		return (NO);
	if (input[i][0] == RED_IN || input[i][0] == RED_OUT || input[i][0] == PIPE)
		return (YES);
	return (NO);
}

int	is_after_red(char **input, int i)
{
	if (i <= 0)
		return (NO);
	if (input[i] && input[i - 1])
		if (input[i - 1][0] == RED_IN || input[i - 1][0] == RED_OUT)
			return (YES);
	return (NO);
}