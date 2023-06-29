#include "../../include/parsing.h"

char	***string_handler(char *input)
{
	t_input	*input_handler;
	char	***res;
	char	*cpy_input;

	res = NULL;
	cpy_input = ft_strdup(input);
	input_handler = create_node();
	cpy_input = quote_handler(cpy_input);
	//var_handler();
	token_separator(cpy_input, &input_handler);
	printf("TOKEN TERMINER\n");
	print_node(input_handler);
	extra_space_handler(&input_handler);
	printf("EXTRA SPACE HANDLER TERMINER\n");
	res = convert_list_to_string(&input_handler);
	free_list(&input_handler);
	ft_xfree(cpy_input);
	printf ("CONVERSION TERMINER\n\n");
	return (res);
}
