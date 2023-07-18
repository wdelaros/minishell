#include "../../include/parsing.h"

static int	need_quote_cleaning(char *str)
{
	if (ft_strlen(str) == 1 && str[0]
		&& (str[0] == DOUBLE_QUOTE || str[0] == SINGLE_QUOTE))
		return (YES);
	return (NO);
}

static void	wagadoo_machine(t_input **ih, int pos)
{
	t_input	*temp;
	t_input	*swap;

	temp = (*ih);
	while (pos > 1)
	{
		temp = temp->next;
		pos--;
	}
	if (temp->next->next)
	{
		swap = temp->next;
		temp->next = temp->next->next;
		temp->next->prev = temp;
		free(swap);
	}
	else if (!temp->next->next)
	{
		swap = temp->next;
		temp = swap;
		free(swap);
	}
}

static void	clean_list(t_input **ih)
{
	t_input	*temp;
	int		pos;

	temp = (*ih);
	pos = 0;
	while (temp->next)
	{
		if (need_quote_cleaning(temp->input) == YES)
			wagadoo_machine(ih, pos);
		if (temp->next)
			temp = temp->next;
		pos++;
	}
}

static int	do_need_cleaning(t_input **ih)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
	{
		if (need_quote_cleaning(temp->input) == YES)
			return (YES);
		temp = temp->next;
	}
	return (NO);
}

static void	change_input(t_input **ih)
{
	t_input	*temp;
	char	*res;
	int		i;
	int		j;
	char	quote;

	temp = (*ih);
	i = 0;
	j = 1;
	while (temp->next)
	{
		if (need_quote_cleaning(temp->input) == YES)
		{
			quote = temp->input[0];
			temp = temp->next;
			res = ft_calloc(ft_strlen(temp->input) + 3, sizeof(char));
			while (temp->input[i])
			{
				if (i == 0)
					res[0] = quote;
				res[j++] = temp->input[i];
				i++;
			}
			res[j] = quote;
			temp->input = res;
			temp = temp->next;
		}
		if (temp->next)
			temp = temp->next;
	}
}

char	***string_handler(char *input, char **env)
{
	t_input	*input_handler;
	char	***res;
	char	*cpy_input;

	res = NULL;
	cpy_input = ft_strdup(input);
	input_handler = create_node();
	cpy_input = var_handler(cpy_input, env);
	token_separator(cpy_input, &input_handler);
	printf("TOKEN TERMINER\n");
	print_node(input_handler);
	if (do_need_cleaning(&input_handler) == YES)
		change_input(&input_handler);
	while (do_need_cleaning(&input_handler) == YES)
		clean_list(&input_handler);
	extra_space_handler(&input_handler);
	printf ("LIST APRES CLEANING:\n");
	print_node(input_handler);
	res = convert_list_to_string(&input_handler);
	free_list(&input_handler);
	ft_xfree(cpy_input);
	printf ("CONVERSION TERMINER\n\n");
	return (res);
}
