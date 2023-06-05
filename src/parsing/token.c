#include "../../include/parsing.h"

/// @brief Seperate the command from the raw input.
/// @param str raw input.
/// @param res the command seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the command has been seperated.
static void	command_separator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[*i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[*i] && (str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE
			&& str[*i] != MINUS && str[*i] != SPACE))
		(*i)++;
	(*i)++;
}

/// @brief Seperate the option from the raw input.
/// @param str raw input.
/// @param res the option seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the option has been seperated.
static void	option_separator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[*i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[*i] && str[*i] != SPACE)
		(*i)++;
	while (str[*i] == SPACE)
		(*i)++;
}

/// @brief Seperate the argument from the raw input.
/// @param str raw input.
/// @param res the argument seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the argument has been seperated.
static void	argument_seperator(char *str, char **res, int *i)
{
	*res = copy_and_join(str, *i);
	if (str[*i] == DOUBLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != DOUBLE_QUOTE)
			(*i)++;
		(*i)++;
	}
	else if (str[*i] == SINGLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != SINGLE_QUOTE)
			(*i)++;
		(*i)++;
	}
	else
		while (str[*i] && str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE)
			(*i)++;
}

static void	token_if(char *str, t_input **ih, int *i)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
		temp = temp->next;
	if (temp->input == NULL && ft_isalpha(str[*i]))
	{
		command_separator(str, &temp->input, i);
		add_node(&temp, COMMAND);
		temp = temp->next;
	}
	if (temp->input == NULL && str[*i] == MINUS)
	{
		option_separator(str, &temp->input, i);
		add_node(&temp, OPTION);
		temp = temp->next;
	}
	if (str[*i] && (str[*i] == DOUBLE_QUOTE || str[*i] == SINGLE_QUOTE
			|| ft_isalpha(str[*i]) || str[*i] == SPACE))
	{
		argument_seperator(str, &temp->input, i);
		add_node(&temp, ARGUMENT);
		temp = temp->next;
	}
}
// A ENLEVER
void	print_node(t_input *list)
{
	while (list)
	{
		printf ("MESSAGE:%s	ID:%d\n", list->input, list->token);
		list = list->next;
	}
}

/// @brief Handle the seperation of the raw input.
/// @param str raw input.
/// @param th token struct.
/// @return No return value.
void	token_separator(char *str, t_input **ih)
{
	int	i;

	i = 0;
	(*ih) = create_node();
	while (str[i])
	{
		token_if(str, ih, &i);
		if (str[i] == SPACE)
			i++;
	}
}
