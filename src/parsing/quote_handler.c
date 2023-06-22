#include "../../include/parsing.h"

//static int	double_quote_handler(char *str, int i)
//{

//}

static int	single_quote_handler(char *str, int i)
{
	char	*temp;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen_until(str, "\'\0", NO);
	temp = ft_calloc(len, sizeof(char));
	i++;
	while (len > 0)
	{
		if (str[i] != SINGLE_QUOTE)
		{
			temp[j] = str[i];
			j++;
			i++;
		}
		len--;
	}
	ft_xfree(str);
	str = temp;
	printf ("%d\n", i);
	return (i);
}

void	quote_handler(t_input **input)
{
	t_input	*temp;
	int		i;

	i = 0;
	temp = (*input);
	while (temp)
	{
		//if (temp->input[i] == DOUBLE_QUOTE)
		//	i = double_quote_handler(temp->input, i);
		if (temp->input[i] == SINGLE_QUOTE)
			i = single_quote_handler(temp->input, i);
		temp = temp->next;
	}
}
