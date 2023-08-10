#include "../../include/parsing.h"

static char	*ft_parsing_cat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (dest);
}

static char	*wagadoo_machine(char *input, int i)
{
	char	*temp;
	int		k;
	int		j;

	k = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(input) + 2, sizeof(char));
	while (input[j])
	{
		if (k == i)
		{
			temp[k++] = input[j++];
			temp[k] = 29;
			k++;
			temp = ft_parsing_cat(temp, &input[j]);
			break ;
		}
		else
		{
			temp[k] = input[j];
			k++;
			j++;
		}
	}
	return (temp);
}

static char	*put_separator(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE)
			i += ft_strlen_until(&input[i], "\"");
		if (input[i] == SINGLE_QUOTE)
			i += ft_strlen_until(&input[i], "\'");
		if (((input[i + 1] == RED_IN || input[i + 1] == RED_OUT
					|| input[i + 1] == PIPE))
			&& input[i] != SPACE && input[i] != 29 && input[i] != RED_OUT
			&& input[i] != RED_IN)
			input = wagadoo_machine(input, i);
		if (((input[i - 1] == RED_IN || input[i - 1] == RED_OUT
					|| input[i - 1] == PIPE))
			&& input[i] != SPACE && input[i] != 29 && input[i] != RED_OUT
			&& input[i] != RED_IN)
			input = wagadoo_machine(input, i - 1);
		if (input[i] == SPACE)
			input[i] = 29;
		i++;
	}
	return (input);
}

char	***string_handler(char *input, char **env)
{
	t_input	*input_handler;
	char	***res;
	char	*cpy_input;

	res = NULL;
	(void) env;
	cpy_input = ft_strdup(input);
	input_handler = create_node();
	cpy_input = put_separator(cpy_input);
	create_list(&input_handler, ft_split(cpy_input, 29));
	quote_handler(&input_handler);
	res = convert_list_to_string(&input_handler);
	free_list(&input_handler);
	ft_xfree(cpy_input);
	printf ("CONVERSION TERMINER\n\n");
	return (res);
}
