#include "../../include/parsing.h"

char	***string_handler(char *input)
{
	t_input	*input_handler;
	char	***res;

	res = NULL;
	input_handler = create_node();
	quote_handler(input);
	//var_handler();
	token_separator(input, &input_handler);
	printf("TOKEN TERMINER\n");
	print_node(input_handler);
	extra_space_handler(&input_handler);
	printf("EXTRA SPACE HANDLER TERMINER\n");
	res = convert_list_to_string(&input_handler);
	free_list(&input_handler);
	printf ("CONVERSION TERMINER\n\n");
	return (res);
}
