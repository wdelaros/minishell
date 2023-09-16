#include "../../include/parsing.h"

int	ft_strlen_until(char *str, char *c)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	j = 0;
	while (c[j])
	{
		i = 0;
		while (str[i])
		{
			if ((str[i] == c[j] && i != 0 && len > i))
				len = i;
			i++;
		}
		j++;
	}
	return (len);
}

void	parsing_xfree_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_xfree(str[i]);
		i++;
	}
	ft_xfree(str);
}

int	skip_quote(char *input, int i, int quote)
{
	i++;
	if (quote == 1)
		while (input[i] && input[i] != SINGLE_QUOTE)
			i++;
	else if (quote == 2)
		while (input[i] && input[i] != DOUBLE_QUOTE)
			i++;
	return (i);
}
