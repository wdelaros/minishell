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

static int	count_space(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SPACE)
			count++;
		i++;
	}
	return (count);
}

static char	*erase_space(char *str)
{
	char	*rep;
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	rep = ft_strdup(str);
	ft_xfree(str);
	res = ft_calloc((ft_strlen(rep) + count_space(rep)) + 1,
			sizeof(char));
	while (rep[j])
	{
		if (rep[j] != SPACE)
		{
			res[i] = rep[j];
			i++;
		}
		j++;
	}
	res[i] = '\0';
	ft_xfree(rep);
	return (res);
}

void	extra_space_handler(t_input **ih)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
	{
		if (is_there_extra_space(temp->input) == YES)
			temp->input = erase_space(temp->input);
		temp = temp->next;
	}
}
