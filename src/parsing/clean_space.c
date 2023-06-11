#include "../../include/parsing.h"

static int	is_there_extra_space(char *str)
{
	if (str[0] == DOUBLE_QUOTE || str[0] == SINGLE_QUOTE)
		return (NO);
	if (str[0] == SPACE)
		return (YES);
	if (str[ft_strlen(str) - 1] == SPACE)
		return (YES);
	return (NO);
}

void	extra_space_handler(t_input **ih)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
	{
		if (is_there_extra_space(temp->input) == YES)
			temp->input = ft_strtrim(temp->input, " ");
		temp = temp->next;
	}
}
