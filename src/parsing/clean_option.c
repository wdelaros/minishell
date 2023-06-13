#include "../../include/parsing.h"

static int	is_option_repetitif(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = i + 1;
		while (input[j])
		{
			if (input[i] == input[j] && !(input[i] == '\0' || input[j] == '\0'))
				return (YES);
			j++;
		}
		i++;
	}
	return (NO);
}

static char	*clean(char *str, char c, int nb)
{
	int		i;
	size_t	j;
	int		keep;
	char	*res;

	i = 0;
	j = 0;
	keep = 1;
	res = NULL;
	res = ft_calloc(ft_strlen(str) - (nb) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == c && keep == 1)
		{
			res[j] = str[i];
			j++;
			keep = 0;
		}
		if (str[i] != c && j < ft_strlen(str) - (nb) + 1)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	return (res);
}

static char	*clean_option(char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		nb = 0;
		while (str[j])
		{
			if (str[i] == str[j] && !(str[i] == '\0' || str[j] == '\0'))
				nb++;
			j++;
		}
		if (nb > 0)
			str = clean(str, str[i], nb);
		i++;
	}
	return (str);
}

void	clean_option_handler(t_input **ih)
{
	t_input	*temp;

	temp = (*ih);
	while (temp)
	{
		if (temp->token == 1)
			if (is_option_repetitif(temp->input) == YES)
				temp->input = clean_option(temp->input);
		temp = temp->next;
	}
}
