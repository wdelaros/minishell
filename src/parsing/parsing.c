#include "../../include/parsing.h"

char	***string_handler(char *input)
{
	t_input	*input_handler;
	char	***res;

	res = NULL;
	input_handler = create_node();
	if (if_all_quote_closed(input, DOUBLE_QUOTE) == 0
		|| if_all_quote_closed(input, SINGLE_QUOTE) == 0)
		printf ("MARDE\n");
	token_separator(input, &input_handler);
	//printf ("SEPARATION DONE, RESULTAT:\n");
	print_node(input_handler);
	extra_space_handler(&input_handler);
	// clean_option_handler(&input_handler);
	//printf ("SPACE_CLEANER_DONE\n");
	// print_node(input_handler);
	//quote_handler(&input_handler);
	res = convert_list_to_string(&input_handler);
	free_list(&input_handler);
	printf ("CONVERSION TERMINER\n\n");
	int	i = 0;
	int	j;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
		{
			Ct_mprintf(res[i][j], ft_strlen(res[i][j]) + 1, 1, 'B');
			j++;
		}
		printf ("\n");
		i++;
	}
	return (res);
}

int	if_all_quote_closed(char *str, int quote)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == quote && flag == 0) // QUOTE OPEN
		{
			flag = 1;
			i++;
		}
		if (str[i] == quote && flag == 1) // QUOTE CLOSED
		{
			flag = 0;
			i++;
		}
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}
