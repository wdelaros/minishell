#include "../../include/parsing.h"

void	print_node(t_input *list)
{
	while (list)
	{
		Ct_mprintf(list->input, ft_strlen(list->input) + 1, 1, 'A');
		printf ("ID: %d\n", list->token);
		list = list->next;
	}
	printf ("\n");
}

t_input	*create_node(void)
{
	t_input	*temp;

	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->token = -1;
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}

void	add_node(t_input **input, int id)
{
	t_input	*current;

	if (*input == NULL)
	{
		(*input) = create_node();
		return ;
	}
	current = (*input);
	while (current->next != NULL)
		current = current->next;
	current->next = create_node();
	if (!current->next)
		return ;
	current->next->prev = current;
	current->token = id;
}

void	free_list(t_input **input_handler)
{
	while ((*input_handler)->next)
		(*input_handler) = (*input_handler)->next;
	if ((*input_handler))
	{
		while ((*input_handler)->prev != NULL)
		{
			(*input_handler) = (*input_handler)->prev;
			free((*input_handler)->next->input);
			free((*input_handler)->next);
		}
		free((*input_handler)->input);
		free((*input_handler));
	}
}
