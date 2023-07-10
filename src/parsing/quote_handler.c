#include "../../include/parsing.h"

static void	quote_eraser(char *res, char *input, int len, char quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (input[i] && input[i] != quote)
		{
			res[j] = input[i];
			j++;
		}
		i++;
	}
}

char	*quote_handler(char *input, int len, char quote)
{
	char	*res;

	printf ("BESOIN D'HANDLER DES QUOTE!\n");
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	quote_eraser(res, input, len, quote);
	return (res);
}
