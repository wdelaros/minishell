#include "../../include/parsing.h"

static int	nb_of_quote(char *str, int i, int c)
{
	int	count;

	count = 1;
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (count + 1);
		i++;
	}
	return (count);
}

// static int	double_quote_handler(char *str, int i)
// {

// }

static int	single_quote_handler(char **str, int i)
{
	char	*temp;
	int		j;

	j = 0;
	printf("COCUOUC JE SUIS UNE SINGLE!\n");
	temp = ft_strdup(*str);
	ft_xfree(*str);
	*str = ft_calloc((ft_strlen(temp) \
	- nb_of_quote(temp, i, SINGLE_QUOTE)) + 1, sizeof(char));
	i++;
	while (temp[i] && temp[i] != SINGLE_QUOTE)
	{
		*str[j] = temp[i];
		j++;
		i++;
	}
	ft_xfree(temp);
	return (i);
}

void	quote_handler(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE)
			i = single_quote_handler(&input, i);
		// else if (input[i] == DOUBLE_QUOTE)
		// 	i = double_quote_handler(input, i);
		i++;
	}
}
